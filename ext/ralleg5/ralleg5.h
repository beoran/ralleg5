#ifndef RALLEG5_INCLUDED
#define RALLEG5_INCLUDED

#include "allegro5/allegro.h"
#include "rubyhelp.h"

extern void ralleg5_display_init(VALUE mAl);
extern void ralleg5_mode_init(VALUE mAl);
extern void ralleg5_monitor_init(VALUE mAl);
extern void ralleg5_color_init(VALUE mAl);
extern void ralleg5_bitmap_init(VALUE mAl);


/* Converts a ruby string to utf-8 */
extern VALUE rb_str_to_utf8(VALUE text);
 
/* Unwraps a Color value to a struct. 
Will return an all zero struct if it had any problems unwrapping the struct. 
*/
extern ALLEGRO_COLOR rbal_color_struct(VALUE rself);

/* Wraps a color struct by ways of allocating a pointer. */
extern VALUE rbal_color_wrap_struct(ALLEGRO_COLOR col);

/* Wraps an ALLEGRO_BITMAP into a ruby VALUE */
extern VALUE rbal_bitmap_wrap(ALLEGRO_BITMAP * ptr); 

/* Wraps bitmaps that allegro manages itself and that should have no 
free function for Ruby. */
VALUE rbal_bitmap_wrap_nofree(ALLEGRO_BITMAP * ptr);

/* Unwraps an ALLEGRO_BITMAP from a ruby VALUE */
extern ALLEGRO_BITMAP * rbal_bitmap_unwrap(VALUE rself);




#endif
