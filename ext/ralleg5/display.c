#include "ralleg5.h"

static VALUE cDisplay;

static VALUE cMode; 

static VALUE cMonitor; 

ALLEGRO_DISPLAY_MODE *rbal_mode_alloc() {
  return calloc(sizeof(ALLEGRO_DISPLAY_MODE), 1);
}

void rbal_mode_free(ALLEGRO_DISPLAY_MODE * ptr) {
  free(ptr);
}

VALUE rbal_mode_wrap(ALLEGRO_DISPLAY_MODE * ptr) {
   if(!ptr) return Qnil;
   return Data_Wrap_Struct(cMode, 0, rbal_mode_free, ptr);
}
  
ALLEGRO_DISPLAY_MODE * rbal_mode_unwrap(VALUE rself) {
  ALLEGRO_DISPLAY_MODE * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_DISPLAY_MODE*, result);
  return result;
}

VALUE rbal_mode_width(VALUE rself) {
  ALLEGRO_DISPLAY_MODE * mode = rbal_mode_unwrap(rself);
  return RBH_INT_NUM(mode->width);
}

VALUE rbal_mode_height(VALUE rself) {
  ALLEGRO_DISPLAY_MODE * mode = rbal_mode_unwrap(rself);
  return RBH_INT_NUM(mode->height);
}

VALUE rbal_mode_format(VALUE rself) {
  ALLEGRO_DISPLAY_MODE * mode = rbal_mode_unwrap(rself);
  return RBH_INT_NUM(mode->format);
}

VALUE rbal_mode_refresh_rate(VALUE rself) {
  ALLEGRO_DISPLAY_MODE * mode = rbal_mode_unwrap(rself);
  return RBH_INT_NUM(mode->refresh_rate);
}

VALUE rbal_mode_amount(VALUE rself) {
  return RBH_INT_NUM(al_get_num_display_modes());
}  

VALUE rbal_mode_get(VALUE rself, VALUE rindex) {
  ALLEGRO_DISPLAY_MODE * mode = rbal_mode_alloc();
  if(!mode) return Qnil;
  al_get_display_mode(RBH_INT(rindex), mode);
  return  rbal_mode_wrap(mode);
}


ALLEGRO_MONITOR_INFO *rbal_monitor_alloc() {
  return calloc(sizeof(ALLEGRO_MONITOR_INFO), 1);
}

void rbal_monitor_free(ALLEGRO_MONITOR_INFO * ptr) {
  free(ptr);
}

VALUE rbal_monitor_wrap(ALLEGRO_MONITOR_INFO * ptr) {
   if(!ptr) return Qnil;
   return Data_Wrap_Struct(cMonitor, 0, rbal_monitor_free, ptr);
}
  
ALLEGRO_MONITOR_INFO * rbal_monitor_unwrap(VALUE rself) {
  ALLEGRO_MONITOR_INFO * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_MONITOR_INFO*, result);
  return result;
}

VALUE rbal_monitor_x1(VALUE rself) {
  ALLEGRO_MONITOR_INFO * self = rbal_mode_unwrap(rself);
  return RBH_INT_NUM(self->x1);
}

VALUE rbal_monitor_x2(VALUE rself) {
  ALLEGRO_MONITOR_INFO * self = rbal_mode_unwrap(rself);
  return RBH_INT_NUM(self->x2);
}

VALUE rbal_monitor_y1(VALUE rself) {
  ALLEGRO_MONITOR_INFO * self = rbal_mode_unwrap(rself);
  return RBH_INT_NUM(self->y1);
}

VALUE rbal_monitor_y2(VALUE rself) {
  ALLEGRO_MONITOR_INFO * self = rbal_mode_unwrap(rself);
  return RBH_INT_NUM(self->y2);
}


VALUE rbal_display_wrap(ALLEGRO_DISPLAY * ptr) {
   if(!ptr) return Qnil;
   return Data_Wrap_Struct(cDisplay, 0, al_destroy_display, ptr);
}

ALLEGRO_DISPLAY * rbal_display_unwrap(VALUE rdisplay) {
  ALLEGRO_DISPLAY * result;
  if (rdisplay == Qnil) return NULL;
  Data_Get_Struct(rdisplay, ALLEGRO_DISPLAY*, result);
  return result;
}  

rbal_create_display(VALUE rself, VALUE rw, VALUE rh) {
  return rbal_display_wrap(al_create_display(RBH_INT(rw), RBH_INT(rh)));
}

rbal_destroy_display(VALUE rself) { 
  ALLEGRO_DISPLAY * display = rbal_display_unwrap(rself);
  al_destroy_display(display);
  return Qnil;
}  


#ifdef _THIS_IS_COMMENT_

/* Possible parameters for al_set_display_option.
 * Make sure to update ALLEGRO_EXTRA_DISPLAY_SETTINGS if you modify
 * anything here.
 */
enum ALLEGRO_DISPLAY_OPTIONS {
   ALLEGRO_RED_SIZE,
   ALLEGRO_GREEN_SIZE,
   ALLEGRO_BLUE_SIZE,
   ALLEGRO_ALPHA_SIZE,
   ALLEGRO_RED_SHIFT,
   ALLEGRO_GREEN_SHIFT,
   ALLEGRO_BLUE_SHIFT,
   ALLEGRO_ALPHA_SHIFT,
   ALLEGRO_ACC_RED_SIZE,
   ALLEGRO_ACC_GREEN_SIZE,
   ALLEGRO_ACC_BLUE_SIZE,
   ALLEGRO_ACC_ALPHA_SIZE,
   ALLEGRO_STEREO,
   ALLEGRO_AUX_BUFFERS,
   ALLEGRO_COLOR_SIZE,
   ALLEGRO_DEPTH_SIZE,
   ALLEGRO_STENCIL_SIZE,
   ALLEGRO_SAMPLE_BUFFERS,
   ALLEGRO_SAMPLES,
   ALLEGRO_RENDER_METHOD,
   ALLEGRO_FLOAT_COLOR,
   ALLEGRO_FLOAT_DEPTH,
   ALLEGRO_SINGLE_BUFFER,
   ALLEGRO_SWAP_METHOD,
   ALLEGRO_COMPATIBLE_DISPLAY,
   ALLEGRO_UPDATE_DISPLAY_REGION,
   ALLEGRO_VSYNC,
   ALLEGRO_MAX_BITMAP_SIZE,
   ALLEGRO_SUPPORT_NPOT_BITMAP,
   ALLEGRO_CAN_DRAW_INTO_BITMAP,
   ALLEGRO_SUPPORT_SEPARATE_ALPHA,
   ALLEGRO_DISPLAY_OPTIONS_COUNT
};

enum
{
   ALLEGRO_DONTCARE,
   ALLEGRO_REQUIRE,
   ALLEGRO_SUGGEST
};


enum ALLEGRO_DISPLAY_ORIENTATION
{
   ALLEGRO_DISPLAY_ORIENTATION_0_DEGREES,
   ALLEGRO_DISPLAY_ORIENTATION_90_DEGREES,
   ALLEGRO_DISPLAY_ORIENTATION_180_DEGREES,
   ALLEGRO_DISPLAY_ORIENTATION_270_DEGREES,
   ALLEGRO_DISPLAY_ORIENTATION_FACE_UP,
   ALLEGRO_DISPLAY_ORIENTATION_FACE_DOWN
};


/* Type: ALLEGRO_DISPLAY
 */
typedef struct ALLEGRO_DISPLAY ALLEGRO_DISPLAY;


/* Type: ALLEGRO_DISPLAY_MODE
 */
typedef struct ALLEGRO_DISPLAY_MODE
{
   int width;
   int height;
   int format;
   int refresh_rate;
} ALLEGRO_DISPLAY_MODE;


/* Type: ALLEGRO_MONITOR_INFO
 */
typedef struct ALLEGRO_MONITOR_INFO
{
   int x1;
   int y1;
   int x2;
   int y2;
} ALLEGRO_MONITOR_INFO;


enum {
   ALLEGRO_DEFAULT_DISPLAY_ADAPTER = -1
};


AL_FUNC(void, al_set_new_display_refresh_rate, (int refresh_rate));
AL_FUNC(void, al_set_new_display_flags, (int flags));
AL_FUNC(int,  al_get_new_display_refresh_rate, (void));
AL_FUNC(int,  al_get_new_display_flags, (void));

AL_FUNC(int, al_get_display_width,  (ALLEGRO_DISPLAY *display));
AL_FUNC(int, al_get_display_height, (ALLEGRO_DISPLAY *display));
AL_FUNC(int, al_get_display_format, (ALLEGRO_DISPLAY *display));
AL_FUNC(int, al_get_display_refresh_rate, (ALLEGRO_DISPLAY *display));
AL_FUNC(int, al_get_display_flags,  (ALLEGRO_DISPLAY *display));
AL_FUNC(bool, al_toggle_display_flag, (ALLEGRO_DISPLAY *display, int flag, bool onoff));

AL_FUNC(ALLEGRO_DISPLAY*, al_create_display, (int w, int h));
AL_FUNC(void,             al_destroy_display, (ALLEGRO_DISPLAY *display));
AL_FUNC(ALLEGRO_DISPLAY*, al_get_current_display, (void));
AL_FUNC(void,            al_set_target_bitmap, (ALLEGRO_BITMAP *bitmap));
AL_FUNC(void,            al_set_target_backbuffer, (ALLEGRO_DISPLAY *display));
AL_FUNC(ALLEGRO_BITMAP*, al_get_backbuffer,    (ALLEGRO_DISPLAY *display));
AL_FUNC(ALLEGRO_BITMAP*, al_get_target_bitmap, (void));

AL_FUNC(bool, al_acknowledge_resize, (ALLEGRO_DISPLAY *display));
AL_FUNC(bool, al_resize_display,     (ALLEGRO_DISPLAY *display, int width, int height));
AL_FUNC(void, al_flip_display,       (void));
AL_FUNC(void, al_update_display_region, (int x, int y, int width, int height));
AL_FUNC(bool, al_is_compatible_bitmap, (ALLEGRO_BITMAP *bitmap));

AL_FUNC(int, al_get_num_display_modes, (void));
AL_FUNC(ALLEGRO_DISPLAY_MODE*, al_get_display_mode, (int index,
        ALLEGRO_DISPLAY_MODE *mode));

AL_FUNC(bool, al_wait_for_vsync, (void));

AL_FUNC(ALLEGRO_EVENT_SOURCE *, al_get_display_event_source, (ALLEGRO_DISPLAY *display));

/* Primitives */
AL_FUNC(void, al_clear_to_color, (ALLEGRO_COLOR color));
AL_FUNC(void, al_draw_pixel, (float x, float y, ALLEGRO_COLOR color));

AL_FUNC(void, al_set_display_icon, (ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *icon));

/* Stuff for multihead/window management */
AL_FUNC(int, al_get_num_video_adapters, (void));
AL_FUNC(bool, al_get_monitor_info, (int adapter, ALLEGRO_MONITOR_INFO *info));
AL_FUNC(int, al_get_new_display_adapter, (void));
AL_FUNC(void, al_set_new_display_adapter, (int adapter));
AL_FUNC(void, al_set_new_window_position, (int x, int y));
AL_FUNC(void, al_get_new_window_position, (int *x, int *y));
AL_FUNC(void, al_set_window_position, (ALLEGRO_DISPLAY *display, int x, int y));
AL_FUNC(void, al_get_window_position, (ALLEGRO_DISPLAY *display, int *x, int *y));

AL_FUNC(void, al_set_window_title, (ALLEGRO_DISPLAY *display, const char *title));

/* Defined in display_settings.c */
AL_FUNC(void, al_set_new_display_option, (int option, int value, int importance));
AL_FUNC(int, al_get_new_display_option, (int option, int *importance));
AL_FUNC(void, al_reset_new_display_options, (void));
AL_FUNC(int, al_get_display_option, (ALLEGRO_DISPLAY *display, int option));

/*Deferred drawing*/
AL_FUNC(void, al_hold_bitmap_drawing, (bool hold));
AL_FUNC(bool, al_is_bitmap_drawing_held, (void));

#endif


void ralleg5_display_init(VALUE mAl) {
  cDisplay = rb_define_class_under(mAl, "Display", rb_cObject);
  cMode    = rb_define_class_under(mAl, "Mode"   , rb_cObject);
  cMonitor = rb_define_class_under(mAl, "Monitor", rb_cObject);
  
  rb_define_method(cMode, "width" , rbal_mode_width, 0);  
  rb_define_method(cMode, "height", rbal_mode_height, 0);  
  rb_define_method(cMode, "format", rbal_mode_format, 0);  
  rb_define_method(cMode, "rate"  , rbal_mode_refresh_rate, 0);  
  rb_define_singleton_method(cMode, "amount", rbal_mode_amount, 0);
  rb_define_singleton_method(cMode, "get"   , rbal_mode_get   , 1);
  
  rb_define_method(cMonitor, "x1", rbal_monitor_x1  , 0);
  rb_define_method(cMonitor, "x2", rbal_monitor_x2  , 0);  
  rb_define_method(cMonitor, "y1", rbal_monitor_y1  , 0);  
  rb_define_method(cMonitor, "y2", rbal_monitor_y2  , 0);  
  
  
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
  rb_define_singleton_method(cDisplay, "create", rbal_create_display, 2);
  rb_define_method(cDisplay, "destroy", rbal_destroy_display, 0);  
}









