#include "ralleg5.h"

static VALUE cMonitor; 

/* Wrappers for monitor info. */

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
  Data_Get_Struct(rself, ALLEGRO_MONITOR_INFO, result);
  return result;
}

VALUE rbal_monitor_x1(VALUE rself) {
  ALLEGRO_MONITOR_INFO * self = rbal_monitor_unwrap(rself);
  return RBH_INT_NUM(self->x1);
}

VALUE rbal_monitor_x2(VALUE rself) {
  ALLEGRO_MONITOR_INFO * self = rbal_monitor_unwrap(rself);
  return RBH_INT_NUM(self->x2);
}

VALUE rbal_monitor_y1(VALUE rself) {
  ALLEGRO_MONITOR_INFO * self = rbal_monitor_unwrap(rself);
  return RBH_INT_NUM(self->y1);
}

VALUE rbal_monitor_y2(VALUE rself) {
  ALLEGRO_MONITOR_INFO * self = rbal_monitor_unwrap(rself);
  return RBH_INT_NUM(self->y2);
}

VALUE rbal_monitor_active(VALUE rself) {
  return RBH_INT_NUM(al_get_new_display_adapter());
}

VALUE rbal_monitor_active_set(VALUE rself, VALUE rindex) {
  al_set_new_display_adapter(RBH_INT(rindex));
  return rbal_monitor_active(rself);
}    

VALUE rbal_monitor_amount(VALUE rself) {
  return RBH_INT_NUM(al_get_num_video_adapters());
}  

VALUE rbal_monitor_get(VALUE rself, VALUE rindex) {
  ALLEGRO_MONITOR_INFO * monitor = rbal_monitor_alloc();
  if(!monitor) return Qnil;
  if(!al_get_monitor_info(RBH_INT(rindex), monitor)) {
    rbal_monitor_free(monitor);
    return Qnil; 
  }
  return rbal_monitor_wrap(monitor);
}

void ralleg5_monitor_init(VALUE mAl) {  
  cMonitor = rb_define_class_under(mAl, "Monitor", rb_cObject);
  rb_define_method(cMonitor, "x1", rbal_monitor_x1  , 0);
  rb_define_method(cMonitor, "x2", rbal_monitor_x2  , 0);  
  rb_define_method(cMonitor, "y1", rbal_monitor_y1  , 0);  
  rb_define_method(cMonitor, "y2", rbal_monitor_y2  , 0);
  rb_define_singleton_method(cMonitor, "amount" , rbal_monitor_amount    , 0);
  rb_define_singleton_method(cMonitor, "get"    , rbal_monitor_get       , 1);
  rb_define_singleton_method(cMonitor, "active" , rbal_monitor_active    , 0);
  rb_define_singleton_method(cMonitor, "active=", rbal_monitor_active_set, 1);
  rb_define_const(cMonitor , "DEFAULT",
  INT2NUM(ALLEGRO_DEFAULT_DISPLAY_ADAPTER));
    
}
