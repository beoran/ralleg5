#include "ralleg5.h"

/* Wrappers for display modes. */

static VALUE cMode; 

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
  Data_Get_Struct(rself, ALLEGRO_DISPLAY_MODE, result);
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

void ralleg5_mode_init(VALUE mAl) {
  cMode    = rb_define_class_under(mAl, "Mode"   , rb_cObject);
  
  rb_define_method(cMode, "width" , rbal_mode_width, 0);  
  rb_define_method(cMode, "height", rbal_mode_height, 0);  
  rb_define_method(cMode, "format", rbal_mode_format, 0);  
  rb_define_method(cMode, "rate"  , rbal_mode_refresh_rate, 0);  
  rb_define_singleton_method(cMode, "amount", rbal_mode_amount, 0);
  rb_define_singleton_method(cMode, "get"   , rbal_mode_get   , 1);
}
