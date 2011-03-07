#include "ralleg5.h"

static VALUE cDisplay;


/* The display itself is wrapped indirectly. */
struct RBAL_DISPLAY_ {
  ALLEGRO_DISPLAY * ptr;
};
 
typedef struct RBAL_DISPLAY_ RBAL_DISPLAY;

/* Allocates the display wrapper */
RBAL_DISPLAY * rbal_display_alloc() {
  return calloc(sizeof(RBAL_DISPLAY), 1); 
}

/* Returns nonzero if the wrapped pointer has been destroyed, zero if not.*/
int rbal_display_free_p(RBAL_DISPLAY * disp) {
  if (!disp) return !0;
  if (!disp->ptr) return !0;
  return 0;
} 

/* Frees the display wrapper, and the enclosed display if needed. */
void rbal_display_free(RBAL_DISPLAY * disp) {
  if(rbal_display_free_p(disp)) return;
  al_destroy_display(disp->ptr);
  disp->ptr = NULL;
}

/* Initializes the display wrapper */
RBAL_DISPLAY * rbal_display_init(RBAL_DISPLAY * disp, ALLEGRO_DISPLAY * ptr) {
  if (!disp) return NULL;
  disp->ptr = ptr; 
  return disp;
}

/* Allocates and frees the display wrapper. */
RBAL_DISPLAY * rbal_display_new(ALLEGRO_DISPLAY * ptr) {
  RBAL_DISPLAY * disp = rbal_display_alloc();  
  if(!rbal_display_init(disp, ptr)) {
    rbal_display_free(disp);
    return NULL;
  }
  return disp;
}


VALUE rbal_display_wrap(ALLEGRO_DISPLAY * ptr) {
   RBAL_DISPLAY * disp = NULL;
   if(!ptr) return Qnil;
   disp = rbal_display_new(ptr);
   if(!disp) return Qnil;
   return Data_Wrap_Struct(cDisplay, 0, rbal_display_free, disp);
}

RBAL_DISPLAY * rbal_display_unwrap_wrapper(VALUE rdisplay) {
  RBAL_DISPLAY * disp = NULL;
  if (rdisplay == Qnil) { return NULL; } 
  Data_Get_Struct(rdisplay, RBAL_DISPLAY, disp);
  return disp;
}  

ALLEGRO_DISPLAY * rbal_display_unwrap(VALUE rdisplay) {
  RBAL_DISPLAY * disp = NULL;
  disp = rbal_display_unwrap_wrapper(rdisplay);
  if (!disp) return NULL;
  return disp->ptr;
}  

VALUE rbal_create_display(VALUE rself, VALUE rw, VALUE rh) {
  return rbal_display_wrap(al_create_display(RBH_INT(rw), RBH_INT(rh)));
}

VALUE rbal_current_display(VALUE rself) {
  return rbal_display_wrap(al_get_current_display());
}

VALUE rbal_destroy_display(VALUE rself) {   
  RBAL_DISPLAY * display = rbal_display_unwrap_wrapper(rself);
  if(rbal_display_free_p(display)) return Qfalse;
  rbal_display_free(display);
  return Qtrue;    
}  

VALUE rbal_display_destroyed_p(VALUE rself) { 
  RBAL_DISPLAY * display = rbal_display_unwrap_wrapper(rself);
  return RBH_INT_BOOL(rbal_display_free_p(display)); 
}  

VALUE rbal_display_width(VALUE rself) { 
  ALLEGRO_DISPLAY * self = rbal_display_unwrap(rself);
  if(!self) return Qnil;
  return RBH_INT_NUM(al_get_display_width(self));
}
  
VALUE rbal_display_height(VALUE rself) { 
  ALLEGRO_DISPLAY * self = rbal_display_unwrap(rself);
  if(!self) return Qnil;
  return RBH_INT_NUM(al_get_display_height(self));
}
  
VALUE rbal_display_format(VALUE rself) { 
  ALLEGRO_DISPLAY * self = rbal_display_unwrap(rself);
  if(!self) return Qnil;
  return RBH_INT_NUM(al_get_display_format(self));
}

VALUE rbal_display_refresh_rate(VALUE rself) { 
  ALLEGRO_DISPLAY * self = rbal_display_unwrap(rself);
  if(!self) return Qnil;
  return RBH_INT_NUM(al_get_display_refresh_rate(self));
}

VALUE rbal_display_flags(VALUE rself) { 
  ALLEGRO_DISPLAY * self = rbal_display_unwrap(rself);
  if(!self) return Qnil;
  return RBH_INT_NUM(al_get_display_flags(self));
}

VALUE rbal_display_toggle_flag(VALUE rself, VALUE rindex, VALUE rbool) { 
  ALLEGRO_DISPLAY * self = rbal_display_unwrap(rself);
  if(!self) return Qnil;
  return RBH_INT_BOOL(al_toggle_display_flag(self, RBH_INT(rindex), RBH_BOOL_INT(rbool)));
}

VALUE rbal_new_display_refresh_rate(VALUE rself) { 
  return RBH_INT_NUM(al_get_new_display_refresh_rate());
}  

VALUE rbal_new_display_flags(VALUE rself) { 
  return RBH_INT_NUM(al_get_new_display_flags());
}  

VALUE rbal_new_display_refresh_rate_(VALUE rself, VALUE rrate) {
  al_set_new_display_refresh_rate(RBH_INT(rrate));
  return rbal_new_display_refresh_rate(rself);
}  

VALUE rbal_new_display_flags_(VALUE rself, VALUE rflags) {
  al_set_new_display_flags(RBH_INT(rflags)); 
  return RBH_INT_NUM(al_get_new_display_flags());
}  

VALUE rbal_new_display_option(VALUE rself, VALUE roption) { 
   int res, importance;
   res = al_get_new_display_option(RBH_INT(roption), &importance);
   /* NOTE: also return importance?*/
   return RBH_INT_NUM(res); 
}   

VALUE rbal_new_display_option_(VALUE rself, VALUE ropt, VALUE rv, VALUE rim) { 
   int importance;
   importance = (rim == Qnil) ? ALLEGRO_SUGGEST : RBH_INT(rim);
   al_set_new_display_option(RBH_INT(ropt), RBH_INT(rv), importance);   
   return rbal_new_display_option(rself, ropt); 
}   

VALUE rbal_new_display_option_reset(VALUE rself) {
   al_reset_new_display_options(); 
   return Qtrue; 
}   

VALUE rbal_acknowledge_resize(VALUE rself) { 
  ALLEGRO_DISPLAY * self = rbal_display_unwrap(rself);
  if(!self) return Qnil;
  return RBH_INT_BOOL(al_acknowledge_resize(self));  
}

VALUE rbal_display_resize(VALUE rself, VALUE rw, VALUE rh) { 
  ALLEGRO_DISPLAY * self = rbal_display_unwrap(rself);
  if(!self) return Qnil;
  return RBH_INT_BOOL(al_resize_display(self, RBH_INT(rw), RBH_INT(rh)));  
}

VALUE rbal_flip_display(VALUE rself) {
  al_flip_display();
  return Qtrue;
}

VALUE rbal_update_region(VALUE rself, VALUE rx, VALUE ry, VALUE rw, VALUE rh) {
  al_update_display_region(RBH_INT(rx), RBH_INT(ry), RBH_INT(rw), RBH_INT(rh));
  return Qtrue;
}

VALUE rbal_vsync(VALUE rself) {
  al_wait_for_vsync();
  return Qtrue;
}

VALUE rbal_new_window_position(VALUE rself) {
  int x = 0, y = 0;
  al_get_new_window_position(&x, &y);
  return rb_ary_new3(2, RBH_INT_NUM(x), RBH_INT_NUM(y));
}  

VALUE rbal_new_window_position_(VALUE rself, VALUE rx, VALUE ry) {
  al_set_new_window_position(RBH_INT(rx), RBH_INT(ry));
  return rbal_new_window_position(rself);
}  

VALUE rbal_display_position(VALUE rself) {
  int x = 0, y = 0;
  ALLEGRO_DISPLAY * self = rbal_display_unwrap(rself);
  if(!self) return Qnil;
  al_get_window_position(self, &x, &y);  
  return rb_ary_new3(2, RBH_INT_NUM(x), RBH_INT_NUM(y));
}  

VALUE rbal_display_position_(VALUE rself, VALUE rx, VALUE ry) {
  ALLEGRO_DISPLAY * self = rbal_display_unwrap(rself);
  if(!self) return Qnil;
  al_set_window_position(self, RBH_INT(rx), RBH_INT(ry));
  return rbal_new_window_position(rself);
}  

VALUE rbal_display_title_(VALUE rself, VALUE rtitle) {
  ALLEGRO_DISPLAY * self = rbal_display_unwrap(rself);
  char * utf8            = RSTRING_PTR(rb_str_to_utf8(rtitle));
  if(!self) return Qnil;
  al_set_window_title(self, utf8);
  return Qtrue;
}  


VALUE rbal_defer_drawing_p(VALUE rself) {
  return RBH_INT_BOOL(al_is_bitmap_drawing_held());
} 

VALUE rbal_defer_drawing(VALUE rself, VALUE rbool) {
  al_hold_bitmap_drawing(RBH_BOOL_INT(rbool));
  return rbal_defer_drawing_p(rself);
} 

/* Backbuffer */
VALUE rbal_display_backbuffer(VALUE rself) {
  ALLEGRO_DISPLAY * self = rbal_display_unwrap(rself);
  return rbal_bitmap_wrap(al_get_backbuffer(self));
}

VALUE rbal_display_set_target(VALUE rself) {
  ALLEGRO_DISPLAY * self = rbal_display_unwrap(rself);
  al_set_target_backbuffer(self);
  return rself;
}

/*
AL_FUNC(void,            al_set_target_backbuffer, (ALLEGRO_DISPLAY *display));
AL_FUNC(ALLEGRO_BITMAP*, al_get_backbuffer,    (ALLEGRO_DISPLAY *display));
AL_FUNC(bool, al_is_compatible_bitmap, (ALLEGRO_BITMAP *bitmap));
*/

/* Drawing */
VALUE rbal_display_clear(VALUE rself, VALUE rcolor) { 
  al_clear_to_color(rbal_color_struct(rcolor));
  return rself;
}  

VALUE rbal_display_draw_pixel(VALUE rself, VALUE rx, VALUE ry, VALUE rcolor) { 
  al_draw_pixel(RBH_FLOAT(rx), RBH_FLOAT(ry), rbal_color_struct(rcolor));
  return rself;
}  

/* Icon */
VALUE rbal_display_icon_(VALUE rself, VALUE rbmp) {
  ALLEGRO_DISPLAY * self = rbal_display_unwrap(rself);
  ALLEGRO_BITMAP  * bmp  = rbal_bitmap_unwrap(rbmp);
  al_set_display_icon(self, bmp);
  return rself;
}


#ifdef _THIS_IS_COMMENT_
/* Still need to implement following when ALLEGRO_COLOR and ALLEGRO_BITMAP 
and ALLEGRO_EVENT_SOURCE are OK. */

AL_FUNC(ALLEGRO_EVENT_SOURCE *, al_get_display_event_source, (ALLEGRO_DISPLAY *display));

/* Primitives */
AL_FUNC(void, al_clear_to_color, (ALLEGRO_COLOR color));
AL_FUNC(void, al_draw_pixel, (float x, float y, ALLEGRO_COLOR color));
AL_FUNC(void, al_set_display_icon, (ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *icon));


#endif


void ralleg5_display_init(VALUE mAl) {
  cDisplay = rb_define_class_under(mAl, "Display", rb_cObject); 
  rb_define_const(cDisplay , "WINDOWED"  	, UINT2NUM(ALLEGRO_WINDOWED));
  rb_define_const(cDisplay , "FULLSCREEN"	, UINT2NUM(ALLEGRO_FULLSCREEN));
  rb_define_const(cDisplay , "OPENGL"   	, UINT2NUM(ALLEGRO_OPENGL));
  rb_define_const(cDisplay , "DIRECT3D" 	, UINT2NUM(ALLEGRO_DIRECT3D_INTERNAL));
  rb_define_const(cDisplay , "RESIZABLE" 	, UINT2NUM(ALLEGRO_RESIZABLE));
  rb_define_const(cDisplay , "NOFRAME" 	, UINT2NUM(ALLEGRO_NOFRAME));
  rb_define_const(cDisplay , "EXPOSE_EVENTS"	, UINT2NUM(ALLEGRO_GENERATE_EXPOSE_EVENTS));
  rb_define_const(cDisplay , "OPENGL3" 	, UINT2NUM(ALLEGRO_OPENGL_3_0));
  rb_define_const(cDisplay , "OPENGL_COMPAT"	, UINT2NUM(ALLEGRO_OPENGL_FORWARD_COMPATIBLE));
  rb_define_const(cDisplay , "FULLSCREEN_WINDOW", UINT2NUM(ALLEGRO_FULLSCREEN_WINDOW));
  rb_define_const(cDisplay , "RED_SIZE", UINT2NUM(ALLEGRO_RED_SIZE));
  rb_define_const(cDisplay , "GREEN_SIZE", UINT2NUM(ALLEGRO_GREEN_SIZE));
  rb_define_const(cDisplay , "BLUE_SIZE", UINT2NUM(ALLEGRO_BLUE_SIZE));
  rb_define_const(cDisplay , "ALPHA_SIZE", UINT2NUM(ALLEGRO_ALPHA_SIZE));
  rb_define_const(cDisplay , "RED_SHIFT", UINT2NUM(ALLEGRO_RED_SHIFT));  
  rb_define_const(cDisplay , "GREEN_SHIFT", UINT2NUM(ALLEGRO_GREEN_SHIFT));
  rb_define_const(cDisplay , "BLUE_SHIFT", UINT2NUM(ALLEGRO_BLUE_SHIFT));
  rb_define_const(cDisplay , "ALPHA_SHIFT", UINT2NUM(ALLEGRO_ALPHA_SHIFT));
  rb_define_const(cDisplay , "ACC_RED_SIZE", UINT2NUM(ALLEGRO_ACC_RED_SIZE));
  rb_define_const(cDisplay , "ACC_GREEN_SIZE", UINT2NUM(ALLEGRO_ACC_GREEN_SIZE));
  rb_define_const(cDisplay , "ACC_BLUE_SIZE", UINT2NUM(ALLEGRO_ACC_BLUE_SIZE));
  rb_define_const(cDisplay , "ACC_ALPHA_SIZE", UINT2NUM(ALLEGRO_ACC_ALPHA_SIZE));
  rb_define_const(cDisplay , "STEREO", UINT2NUM(ALLEGRO_STEREO));
  rb_define_const(cDisplay , "AUX_BUFFERS", UINT2NUM(ALLEGRO_AUX_BUFFERS));
  rb_define_const(cDisplay , "COLOR_SIZE", UINT2NUM(ALLEGRO_COLOR_SIZE));
  rb_define_const(cDisplay , "DEPTH_SIZE", UINT2NUM(ALLEGRO_DEPTH_SIZE));
  rb_define_const(cDisplay , "STENCIL_SIZE", UINT2NUM(ALLEGRO_STENCIL_SIZE));
  rb_define_const(cDisplay , "SAMPLE_BUFFERS", UINT2NUM(ALLEGRO_SAMPLE_BUFFERS));
  rb_define_const(cDisplay , "SAMPLES", UINT2NUM(ALLEGRO_SAMPLES));
  rb_define_const(cDisplay , "RENDER_METHOD", UINT2NUM(ALLEGRO_RENDER_METHOD));
  rb_define_const(cDisplay , "FLOAT_COLOR", UINT2NUM(ALLEGRO_FLOAT_COLOR));
  rb_define_const(cDisplay , "FLOAT_DEPTH", UINT2NUM(ALLEGRO_FLOAT_DEPTH));
  rb_define_const(cDisplay , "SINGLE_BUFFER", UINT2NUM(ALLEGRO_SINGLE_BUFFER));
  rb_define_const(cDisplay , "SWAP_METHOD", UINT2NUM(ALLEGRO_SWAP_METHOD));
  rb_define_const(cDisplay , "COMPATIBLE_DISPLAY", UINT2NUM(ALLEGRO_COMPATIBLE_DISPLAY));
  rb_define_const(cDisplay , "UPDATE_DISPLAY_REGION",
                              UINT2NUM(ALLEGRO_UPDATE_DISPLAY_REGION));
  rb_define_const(cDisplay , "VSYNC", UINT2NUM(ALLEGRO_VSYNC));
  rb_define_const(cDisplay , "MAX_BITMAP_SIZE", UINT2NUM(ALLEGRO_MAX_BITMAP_SIZE));
  rb_define_const(cDisplay , "SUPPORT_NPOT_BITMAP", 
                              UINT2NUM(ALLEGRO_SUPPORT_NPOT_BITMAP));
  rb_define_const(cDisplay , "CAN_DRAW_INTO_BITMAP", 
                            UINT2NUM(ALLEGRO_CAN_DRAW_INTO_BITMAP));
  rb_define_const(cDisplay , "SUPPORT_SEPATATE_ALPHA",
                            UINT2NUM(ALLEGRO_SUPPORT_SEPARATE_ALPHA));
  rb_define_const(cDisplay , "OPTIONS_COUNT", UINT2NUM(ALLEGRO_DISPLAY_OPTIONS_COUNT));
  rb_define_const(cDisplay , "DONTCARE", UINT2NUM(ALLEGRO_DONTCARE));
  rb_define_const(cDisplay , "REQUIRE", UINT2NUM(ALLEGRO_REQUIRE));
  rb_define_const(cDisplay , "SUGGEST", UINT2NUM(ALLEGRO_SUGGEST));
  
  rb_define_const(cDisplay , "ORIENTATION_0_DEGREES",
                              UINT2NUM(ALLEGRO_DISPLAY_ORIENTATION_0_DEGREES));
  rb_define_const(cDisplay , "ORIENTATION_90_DEGREES",
                              UINT2NUM(ALLEGRO_DISPLAY_ORIENTATION_90_DEGREES));
  rb_define_const(cDisplay , "ORIENTATION_180_DEGREES",
                              UINT2NUM(ALLEGRO_DISPLAY_ORIENTATION_180_DEGREES));
  rb_define_const(cDisplay , "ORIENTATION_270_DEGREES",
                              UINT2NUM(ALLEGRO_DISPLAY_ORIENTATION_270_DEGREES));
                            
  rb_define_const(cDisplay , "ORIENTATION_FACE_UP",
                              UINT2NUM(ALLEGRO_DISPLAY_ORIENTATION_FACE_UP));
  rb_define_const(cDisplay , "ORIENTATION_FACE_DOWN",
                              UINT2NUM(ALLEGRO_DISPLAY_ORIENTATION_FACE_DOWN));
   
  
  rb_define_singleton_method(cDisplay, "create", rbal_create_display, 2);
  rb_define_singleton_method(cDisplay, "current", rbal_current_display, 0);
  rb_define_singleton_method(cDisplay, "rate"  , rbal_new_display_refresh_rate, 0);
  rb_define_singleton_method(cDisplay, "rate=" , rbal_new_display_refresh_rate_, 1);
  rb_define_singleton_method(cDisplay, "flags" , rbal_new_display_flags, 0);
  rb_define_singleton_method(cDisplay, "flags=", rbal_new_display_flags_, 1);
  rb_define_singleton_method(cDisplay, "option", rbal_new_display_option, 1);
  rb_define_singleton_method(cDisplay, "option_set", rbal_new_display_option_, 3);
  rb_define_singleton_method(cDisplay, "option_reset", 
  rbal_new_display_option_reset, 0);
  
  rb_define_singleton_method(cDisplay, "acknowledge_resize"
                                     , rbal_acknowledge_resize, 0);
  rb_define_method(cDisplay, "resize", rbal_display_resize, 2);
  rb_define_singleton_method(cDisplay, "flip", rbal_flip_display, 0);
  rb_define_singleton_method(cDisplay, "update_region", rbal_update_region, 4);
  rb_define_singleton_method(cDisplay, "vsync"   , rbal_vsync, 0);
  rb_define_singleton_method(cDisplay, "position", rbal_new_window_position, 0);
  rb_define_singleton_method(cDisplay, "position_set", rbal_new_window_position_, 2);
  
  rb_define_method(cDisplay, "position"    , rbal_display_position, 0);
  rb_define_method(cDisplay, "position_set", rbal_display_position_, 2);
  rb_define_method(cDisplay, "title="      , rbal_display_title_   , 1);
  rb_define_method(cDisplay, "icon="       , rbal_display_icon_    , 1);  
  
  rb_define_singleton_method(cDisplay, "defer?", rbal_defer_drawing_p, 0);
  rb_define_singleton_method(cDisplay, "defer!", rbal_defer_drawing, 1);
  rb_define_singleton_method(cDisplay, "clear_to", rbal_display_clear , 1);
  rb_define_singleton_method(cDisplay, "putpixel", rbal_display_draw_pixel , 3);
  
  
  rb_define_method(cDisplay, "destroy", rbal_destroy_display, 0);
  rb_define_method(cDisplay, "destroy?", rbal_display_destroyed_p, 0);
  rb_define_method(cDisplay, "width"   , rbal_display_width, 0);
  rb_define_method(cDisplay, "height"  , rbal_display_height, 0);
  rb_define_method(cDisplay, "format"  , rbal_display_format, 0);
  rb_define_method(cDisplay, "rate"    , rbal_display_refresh_rate, 0);
  rb_define_method(cDisplay, "flags"   , rbal_display_flags, 0);
  rb_define_method(cDisplay, "toggle_flag", rbal_display_toggle_flag, 2);
  rb_define_method(cDisplay, "backbuffer" , rbal_display_backbuffer , 0);
  rb_define_method(cDisplay, "target!"    , rbal_display_set_target , 0);
  
}









