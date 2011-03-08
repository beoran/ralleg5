#include "ralleg5.h"


static VALUE cJoystickState;

ALLEGRO_JOYSTICK_STATE * rbal_joystickstate_alloc() {
  return calloc(sizeof(ALLEGRO_JOYSTICK_STATE), 1);
}

VALUE rbal_joystickstate_wrap(ALLEGRO_JOYSTICK_STATE * ptr) {
   if(!ptr) return Qnil;
   return Data_Wrap_Struct(cJoystickState, 0, 0, ptr);
}
  
ALLEGRO_JOYSTICK_STATE * rbal_joystickstate_unwrap(VALUE rself) {
  ALLEGRO_JOYSTICK_STATE * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_JOYSTICK_STATE, result);
  return result;
}

VALUE rbal_joystickstate_button(VALUE rself, VALUE rindex) {
  ALLEGRO_JOYSTICK_STATE * self = rbal_joystickstate_unwrap(rself);
  int index = RBH_INT(rindex);
  if ((index < 0) || (index >= _AL_MAX_JOYSTICK_BUTTONS)) return Qnil;
  return RBH_INT_NUM(self->button[index]);
}

VALUE rbal_joystickstate_axis(VALUE rself, VALUE rstick, VALUE raxis) {
  ALLEGRO_JOYSTICK_STATE * self = rbal_joystickstate_unwrap(rself);
  int stick = RBH_INT(rstick);
  int axis  = RBH_INT(raxis);
  if ((stick < 0) || (stick >= _AL_MAX_JOYSTICK_STICKS)) return Qnil;
  if ((axis  < 0) || (axis  >= _AL_MAX_JOYSTICK_AXES)) return Qnil;
  return RBH_FLOAT_NUM(self->stick[stick].axis[axis]);
}


static VALUE cJoystick; 

/* Wrappers for Joystick. */

VALUE rbal_joystick_wrap(ALLEGRO_JOYSTICK * ptr) {
   if(!ptr) return Qnil;
   return Data_Wrap_Struct(cJoystick, 0, al_release_joystick, ptr);
}
  
ALLEGRO_JOYSTICK * rbal_joystick_unwrap(VALUE rself) {
  ALLEGRO_JOYSTICK * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_JOYSTICK, result);
  return result;
}

VALUE rbal_joystick_init(VALUE rself) {
  return RBH_INT_BOOL(al_install_joystick());
}
   
VALUE rbal_joystick_init_p(VALUE rself) {
  return RBH_INT_BOOL(al_is_joystick_installed());
}
   
VALUE rbal_joystick_done(VALUE rself) {
  al_uninstall_joystick();
  return rself;
}

VALUE rbal_joystick_reconfigure(VALUE rself) {
  return RBH_INT_BOOL(al_reconfigure_joysticks());
}

VALUE rbal_joystick_amount(VALUE rself) {
  return RBH_INT_NUM(al_get_num_joysticks());
}

VALUE rbal_joystick_get(VALUE rself, VALUE rindex) {
  return rbal_joystick_wrap(al_get_joystick(RBH_INT(rindex)));
}

VALUE rbal_joystick_active_p(VALUE rself) {
  ALLEGRO_JOYSTICK * self = rbal_joystick_unwrap(rself);
  return RBH_INT_BOOL(al_get_joystick_active(self));
}  

VALUE rbal_joystick_name(VALUE rself) {
  ALLEGRO_JOYSTICK * self = rbal_joystick_unwrap(rself);
  const char * name = al_get_joystick_name(self);
  return RBH_STR_UTF82(name);
}  

VALUE rbal_joystick_sticks(VALUE rself) {
  ALLEGRO_JOYSTICK * self = rbal_joystick_unwrap(rself);
  return RBH_INT_NUM(al_get_joystick_num_sticks(self));
}  

VALUE rbal_joystick_axes(VALUE rself, VALUE rstick) {
  ALLEGRO_JOYSTICK * self = rbal_joystick_unwrap(rself);
  return RBH_INT_NUM(al_get_joystick_num_axes(self, RBH_INT(rstick)));
}  

VALUE rbal_joystick_buttons(VALUE rself) {
  ALLEGRO_JOYSTICK * self = rbal_joystick_unwrap(rself);
  return RBH_INT_NUM(al_get_joystick_num_buttons(self));
}  

VALUE rbal_joystick_stick_name(VALUE rself, VALUE rindex) {
  ALLEGRO_JOYSTICK * self = rbal_joystick_unwrap(rself);
  const char * name = al_get_joystick_stick_name(self, RBH_INT(rindex));
  return RBH_STR_UTF82(name);
}  

VALUE rbal_joystick_axis_name(VALUE rself, VALUE rstick, VALUE rindex) {
  ALLEGRO_JOYSTICK * self = rbal_joystick_unwrap(rself);
  const char * name = al_get_joystick_axis_name(self, 
                  RBH_INT(rstick), RBH_INT(rindex));
  return RBH_STR_UTF82(name);
}  

VALUE rbal_joystick_button_name(VALUE rself, VALUE rindex) {
  ALLEGRO_JOYSTICK * self = rbal_joystick_unwrap(rself);
  const char * name = al_get_joystick_button_name(self, RBH_INT(rindex));
  return RBH_STR_UTF82(name);
}  

VALUE rbal_joystick_stick_flags(VALUE rself, VALUE rindex) {
  ALLEGRO_JOYSTICK * self = rbal_joystick_unwrap(rself);
  return RBH_INT_NUM(al_get_joystick_stick_flags(self, RBH_INT(rindex)));
}  

VALUE rbal_joystick_state(VALUE rself) {
  ALLEGRO_JOYSTICK * self = rbal_joystick_unwrap(rself);
  ALLEGRO_JOYSTICK_STATE * state = rbal_joystickstate_alloc();
  if(!state) return Qnil;
  al_get_joystick_state(self, state);  
  return rbal_joystickstate_wrap(state);
}    



/*
   ALLEGRO_JOYFLAG_DIGITAL  = 0x01,
   ALLEGRO_JOYFLAG_ANALOGUE = 0x02
*/

VALUE rbal_joystick_eventsource(VALUE rself) { 
  return rbal_eventsource_wrap_nofree(al_get_joystick_event_source());
}

void ralleg5_joystickstate_init(VALUE mAl) {
  cJoystickState  = rb_define_class_under(mAl, "JoystickState" , rb_cObject);
  rb_define_method(cJoystickState, "button" , rbal_joystickstate_button, 1);
  rb_define_method(cJoystickState, "axis"   , rbal_joystickstate_axis  , 2);
}  

void ralleg5_joystick_init(VALUE mAl) {
  ralleg5_joystickstate_init(mAl);
    
  cJoystick   = rb_define_class_under(mAl, "Joystick"   , rb_cObject);  
  rb_define_singleton_method(cJoystick, "init", rbal_joystick_init, 0);
  rb_define_singleton_method(cJoystick, "init?", rbal_joystick_init_p, 0);
  rb_define_singleton_method(cJoystick, "done", rbal_joystick_done, 0);
  rb_define_singleton_method(cJoystick, "eventsource",
                                         rbal_joystick_eventsource, 0);
  rb_define_singleton_method(cJoystick, "reconfigure", 
                                        rbal_joystick_reconfigure, 0);
  rb_define_singleton_method(cJoystick, "amount", rbal_joystick_amount, 0);
  rb_define_singleton_method(cJoystick, "get", rbal_joystick_get, 1);
  
    
  rb_define_method(cJoystick, "axes"    , rbal_joystick_axes   , 1);
  rb_define_method(cJoystick, "buttons" , rbal_joystick_buttons, 0);
  rb_define_method(cJoystick, "sticks"  , rbal_joystick_sticks , 0);
  
  rb_define_method(cJoystick, "name"    , rbal_joystick_name, 0);
  rb_define_method(cJoystick, "active?" , rbal_joystick_active_p, 0);
  rb_define_method(cJoystick, "stick_name", rbal_joystick_stick_name, 1);
  rb_define_method(cJoystick, "button_name" , rbal_joystick_button_name, 1);
  rb_define_method(cJoystick, "axis_name" , rbal_joystick_axis_name, 2);
  rb_define_method(cJoystick, "stick_flags" , rbal_joystick_stick_flags, 1);
  rb_define_method(cJoystick, "state"       , rbal_joystick_state, 0);    
    
}















