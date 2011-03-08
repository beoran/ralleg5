#include "ralleg5.h"


/* This is a small template for many common functions 

#include "ralleg5.h"

static VALUE cXXX;

ALLEGRO_YYY * rbal_xxx_alloc() {
  return calloc(sizeof(ALLEGRO_YYY), 1);
}

void rbal_xxx_free(ALLEGRO_YYY * ptr) {
  free(ptr);
}

VALUE rbal_xxx_wrap(ALLEGRO_YYY * ptr) {
   if(!ptr) return Qnil;
   return Data_Wrap_Struct(cXXX, 0, 0, ptr);
}
  
ALLEGRO_YYY * rbal_joystickstate_unwrap(VALUE rself) {
  ALLEGRO_YYY * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_YYY, result);
  return result;
}


VALUE rbal_xxx_init(VALUE rself) {
  return RBH_INT_BOOL(al_install_xxx());
}
   
VALUE rbal_xxx_init_p(VALUE rself) {
  return RBH_INT_BOOL(al_is_xxx_installed());
}
   
VALUE rbal_xxx_done(VALUE rself) {
  al_uninstall_xxx();
  return rself;
}




void ralleg5__init(VALUE mAl) {
  cXXX = rb_define_class_under(mAl, "XXX"   , rb_cObject);
  rb_define_singleton_method(cXXX, "init"    , rbal_mouse_init   , 0);
  rb_define_singleton_method(cXXX, "init?"   , rbal_mouse_init_p , 0);
  rb_define_singleton_method(cXXX, "done"    , rbal_mouse_done   , 0);
}

*/

