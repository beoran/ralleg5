 /* A program to compare allegro 5, CSFML 1.6  and SDL 1.2  in C.
 * gcc test_tilemap.c -lSDL -lSDL_image -lallegro -lallegro_image -o test_tilemap
 * Looks like on old PC's with no HW acceleration, allegro is at least
 * 4 times slower than SDL.
 * Typical measurements: 
 * 
 * SDL:
 * Delta, fps: 1.701000, 58.788948
 *
 * Allegro: 
 * Delta, fps: 7.620342, 13.122771
 *
 * CSFML: 
 * Diplays nothing, and seems to take the same time as Allegro.
 *
 */


#include <stdio.h>

#define REPEATS 1000
#ifndef USE_SDL
#define USE_ALLEGRO
#endif
/* #undef USE_SDL */

#ifdef USE_ALLEGRO 
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#elif defined USE_SFML 

#include <SFML/Graphics.h>
 

#else
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#endif


#ifdef USE_ALLEGRO
int main(void) {
  int x, y, dx, dy, rep;
  double start, stop, delta;
  
  
  ALLEGRO_DISPLAY * disp = NULL;
  ALLEGRO_BITMAP *  bmp = NULL;
  al_init();
  al_init_image_addon();
      
  disp = al_create_display(640, 460);
  /* al_set_blender(ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, solid); */
  al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);
  
  if(!disp) {
    puts("Could not open display.");
    return -1;
  }
  
  
  bmp = al_load_bitmap("../data/tile_grass.png");
  if(!bmp) {
    puts("Could not open bit map.");
    return -1;
  }
  puts("2");
  
  start = al_get_time();
  for (rep = 0; rep < REPEATS; rep ++) {    
    for(dx = 0; dx < 640; dx += 32) {
      for(dy = 0; dy < 480; dy += 32) {
        al_draw_bitmap(bmp, dx, dy, 0); 
      }
    } 
    al_flip_display();
  }
  stop = al_get_time();
  delta = stop - start;
  printf("Delta, fps: %lf, %lf\n", delta, (double)REPEATS / delta);

  al_destroy_bitmap(bmp);
  al_destroy_display(disp);
  return 0;
}
#elif defined USE_SFML

#include <time.h>

 int main() {
  int x, y, rep;
  clock_t start, stop, delta;
  float dx, dy;
  double secs;

  sfWindowSettings settings = {24, 8, 0};
  sfVideoMode      mode     = {800, 600, 16};
  sfRenderWindow            * disp;
  sfImage                   * bmp;
  sfSprite                  * sprite;
  /* Create the main window */
  disp = sfRenderWindow_Create(mode, "SFML", sfTitlebar, settings);
  if (!disp)  return EXIT_FAILURE;

  /* Load a sprite to display */
  bmp = sfImage_CreateFromFile("../data/tile_grass.png");     
  if (!bmp)
      return EXIT_FAILURE;
  sprite = sfSprite_Create();
  sfSprite_SetImage(sprite, bmp);
  start = clock(); 
  for (rep = 0; rep < REPEATS; rep ++) {
    for(dx = 0.0; dx < 640.0; dx += 32.0) {
      for(dy = 0.0; dy < 480.0; dy += 32.0) {
        sfSprite_SetX(sprite, dx);
        sfSprite_SetY(sprite, dy);
        sfRenderWindow_DrawSprite(disp, sprite);
      }
    }
    sfRenderWindow_Display(disp);
  }
  stop = clock();
  delta = stop - start;
  secs  = ((double)delta) / ((double)CLOCKS_PER_SEC);
  printf("Delta, fps: %lf (%ld), %lf\n", secs, delta, 100.0 / secs);
  /* Cleanup resources */
  sfSprite_Destroy(sprite);
  sfImage_Destroy(bmp);
  sfRenderWindow_Destroy(disp); 
  return EXIT_SUCCESS;
}




#else

int main(void) {
  int x, y, dx, dy, rep;
  int start, stop, delta;
  SDL_Rect aid;
  
  SDL_Surface    * disp = NULL;
  SDL_Surface    *  bmp = NULL;
  SDL_Surface    *  opt = NULL;
  
  SDL_Init(SDL_INIT_EVERYTHING);
  disp =  SDL_SetVideoMode(640, 480, 16, SDL_ANYFORMAT | SDL_DOUBLEBUF);  
    
  
  if(!disp) {
    puts("Could not open display.");     
    return -1;
  }
  
  
  bmp = IMG_Load("../data/tile_grass.png");
  if(!bmp) {
    puts("Could not open bit map.");
    return -1;
  }
  opt = SDL_DisplayFormat(bmp);  
  puts("2");
  
  start = SDL_GetTicks();
  aid.w = 32;
  aid.h = 32;
  for (rep = 0; rep < REPEATS; rep ++) {
    for(dx = 0; dx < 640; dx += 32) {
      for(dy = 0; dy < 480; dy += 32) {
        aid.x = dx;
        aid.y = dy;
        SDL_BlitSurface(opt, NULL, disp, &aid); 
      }
    } 
    SDL_Flip(disp);
  }
  stop  = SDL_GetTicks();
  delta = stop - start;
  printf("Delta, fps: %lf, %lf\n", ((double)delta) / 1000.0
                                 , (1000.0 * ((double)REPEATS)) / ((double)delta));
  SDL_FreeSurface(opt);
  SDL_FreeSurface(bmp);
  SDL_Quit();  
  return 0;
}
#endif


