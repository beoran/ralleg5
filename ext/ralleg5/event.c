#include "ralleg5.h"



static VALUE cEventSource;


VALUE rbal_eventsource_wrap_nofree(ALLEGRO_EVENT_SOURCE * ptr) {   
   if(!ptr) return Qnil;
   return Data_Wrap_Struct(cEventSource, 0, 0, ptr);
}

ALLEGRO_EVENT_SOURCE * rbal_eventsource_unwrap(VALUE rself) {
  ALLEGRO_EVENT_SOURCE * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_EVENT_SOURCE, result);
  return result;
}


static VALUE cEvent;

void rbal_event_free(ALLEGRO_EVENT * ptr) {
  free(ptr);
}

ALLEGRO_EVENT * rbal_event_alloc() {
  return calloc(sizeof(ALLEGRO_EVENT), 1);
}

VALUE rbal_event_wrap(ALLEGRO_EVENT * ptr) {
   if(!ptr) return Qnil;
   return Data_Wrap_Struct(cEvent, 0, rbal_event_free, ptr);
}

ALLEGRO_EVENT * rbal_event_unwrap(VALUE rself) {
  ALLEGRO_EVENT * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_EVENT, result);
  return result;
}

VALUE rbal_event_type(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if(!self) return Qnil;
  return RBH_INT_NUM(self->type); 
}
 
/*  srctype *source;  is harder, as it varies upon  the event type */
 
VALUE rbal_event_timestamp(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if(!self) return Qnil;
  return RBH_DOUBLE_NUM(self->any.timestamp); 
} 

/* Checks if an event is a display event. */
int rbal_event_is_display(ALLEGRO_EVENT * event) {
  if(!event) return 0;
  if ((event->type >= ALLEGRO_EVENT_DISPLAY_EXPOSE) &&
      (event->type <= ALLEGRO_EVENT_DISPLAY_ORIENTATION)) {
     return (!0);
  }   
  return 0;
}

/* Checks if an event is a joystick event. */
int rbal_event_is_joystick(ALLEGRO_EVENT * event) {
  if(!event) return 0;
  if ((event->type >= ALLEGRO_EVENT_JOYSTICK_AXIS) &&
     (event->type <= ALLEGRO_EVENT_JOYSTICK_CONFIGURATION)) {
     return (!0);
  }   
  return 0;
}

/* Checks if an event is a keyboard event. */
int rbal_event_is_keyboard(ALLEGRO_EVENT * event) {
  if(!event) return 0;
  if ((event->type >= ALLEGRO_EVENT_KEY_DOWN) &&
     (event->type <= ALLEGRO_EVENT_KEY_UP)) {
     return (!0);
  }   
  return 0;
}


/* Checks if an event is a mouse event. */
int rbal_event_is_mouse(ALLEGRO_EVENT * event) {
  if(!event) return 0;
  if ((event->type >= ALLEGRO_EVENT_MOUSE_AXES) &&
     (event->type <= ALLEGRO_EVENT_MOUSE_WARPED)) {
     return (!0);
  }   
  return 0;
}

/* Checks if an event is a timer event. */
int rbal_event_is_timer(ALLEGRO_EVENT * event) {
  if(!event) return 0;
  if ((event->type == ALLEGRO_EVENT_TIMER)) {
     return (!0);
  }   
  return 0;
}

/* Ruby wrappers for the above */

VALUE rbal_event_display_p(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  return RBH_INT_BOOL(rbal_event_is_display(self));  
}

VALUE rbal_event_joystick_p(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  return RBH_INT_BOOL(rbal_event_is_joystick(self));  
}

VALUE rbal_event_keyboard_p(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  return RBH_INT_BOOL(rbal_event_is_keyboard(self));  
}

VALUE rbal_event_mouse_p(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  return RBH_INT_BOOL(rbal_event_is_mouse(self));  
}

VALUE rbal_event_timer_p(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  return RBH_INT_BOOL(rbal_event_is_timer(self));  
}


VALUE rbal_event_x(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (rbal_event_is_mouse(self)) { 
    return RBH_INT_NUM(self->mouse.x);
  } else if (rbal_event_is_display(self)) {
    return RBH_INT_NUM(self->display.x);
  }   
  return Qnil;
}

VALUE rbal_event_y(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (rbal_event_is_mouse(self)) { 
    return RBH_INT_NUM(self->mouse.y);
  } else if (rbal_event_is_display(self)) {
    return RBH_INT_NUM(self->display.y);
  }   
  return Qnil;
}

VALUE rbal_event_button(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (rbal_event_is_mouse(self)) { 
    return RBH_INT_NUM(self->mouse.button);
  } else if (rbal_event_is_joystick(self)) {
    return RBH_INT_NUM(self->joystick.button);
  }   
  return Qnil;
}

VALUE rbal_event_width(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (!rbal_event_is_display(self)) return Qnil;
  return RBH_INT_NUM(self->display.width);
}

VALUE rbal_event_height(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (!rbal_event_is_display(self)) return Qnil;
  return RBH_INT_NUM(self->display.height);
}

VALUE rbal_event_orientation(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (!rbal_event_is_display(self)) return Qnil;
  return RBH_INT_NUM(self->display.orientation);
}

VALUE rbal_event_stick(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (!rbal_event_is_joystick(self)) return Qnil;
  return RBH_INT_NUM(self->joystick.stick);
}

VALUE rbal_event_axis(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (!rbal_event_is_joystick(self)) return Qnil;
  return RBH_INT_NUM(self->joystick.axis);
}

VALUE rbal_event_pos(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (!rbal_event_is_joystick(self)) return Qnil;
  return RBH_FLOAT_NUM(self->joystick.pos);
}

/* joystick ID, to implement when ALLEGRO_JOYSTICK is ok. */
VALUE rbal_event_id(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (!rbal_event_is_joystick(self)) return Qnil;
  // TODO: implement correctly
  // return rbal_joystick_wrap(self->joystick.id);
  return Qnil;
}

VALUE rbal_event_display(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (rbal_event_is_keyboard(self)) { 
    return rbal_wrap_display_nofree(self->keyboard.display);
  } else if (rbal_event_is_display(self)) {
    return rbal_wrap_display_nofree(self->display.source);
  } else if (rbal_event_is_mouse(self)) {
    return rbal_wrap_display_nofree(self->mouse.source);
  }
  return Qnil;
}

VALUE rbal_event_keycode(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (!rbal_event_is_keyboard(self)) return Qnil;
  return RBH_INT_NUM(self->keyboard.keycode);
}


VALUE rbal_event_unichar(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (!rbal_event_is_keyboard(self)) return Qnil;
  return RBH_INT_NUM(self->keyboard.unichar);
}

VALUE rbal_event_modifiers(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (!rbal_event_is_keyboard(self)) return Qnil;
  return RBH_UINT_NUM(self->keyboard.modifiers);
}

VALUE rbal_event_repeat(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (!rbal_event_is_keyboard(self)) return Qnil;
  return RBH_INT_BOOL(self->keyboard.repeat);
}


VALUE rbal_event_z(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (!rbal_event_is_mouse(self)) return Qnil;
  return RBH_INT_NUM(self->mouse.z);
}

VALUE rbal_event_dx(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (!rbal_event_is_mouse(self)) return Qnil;
  return RBH_INT_NUM(self->mouse.dx);
}

VALUE rbal_event_dy(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (!rbal_event_is_mouse(self)) return Qnil;
  return RBH_INT_NUM(self->mouse.dy);
}

VALUE rbal_event_dz(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (!rbal_event_is_mouse(self)) return Qnil;
  return RBH_INT_NUM(self->mouse.dz);
}

VALUE rbal_event_pressure(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (!rbal_event_is_mouse(self)) return Qnil;
  return RBH_FLOAT_NUM(self->mouse.pressure);
}


VALUE rbal_event_count(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (!rbal_event_is_timer(self)) return Qnil;
  // FIXME: this will overflow, Ruby may not be able to handle 64 bits values. 
  return RBH_INT_NUM(self->timer.count);
}

VALUE rbal_event_error(VALUE rself) {
  ALLEGRO_EVENT * self = rbal_event_unwrap(rself);
  if (!rbal_event_is_timer(self)) return Qnil;
  return RBH_FLOAT_NUM(self->timer.error);
}





/* Event queues */

static VALUE cEventQueue;

VALUE rbal_eventqueue_wrap(ALLEGRO_EVENT_QUEUE * ptr) {   
   if(!ptr) return Qnil;
   return Data_Wrap_Struct(cEventQueue, 0, al_destroy_event_queue, ptr);
}

ALLEGRO_EVENT_QUEUE * rbal_eventqueue_unwrap(VALUE rself) {
  ALLEGRO_EVENT_QUEUE * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_EVENT_QUEUE, result);
  return result;
}

VALUE rbal_eventqueue_new(VALUE rself) {
  return rbal_eventqueue_wrap(al_create_event_queue()); 
}

VALUE rbal_eventqueue_register(VALUE rself, VALUE rsrc) {
   ALLEGRO_EVENT_QUEUE  * self = rbal_eventqueue_unwrap(rself);
   ALLEGRO_EVENT_SOURCE * src  = rbal_eventsource_unwrap(rsrc);
   al_register_event_source(self, src);
   return rself;
}

VALUE rbal_eventqueue_unregister(VALUE rself, VALUE rsrc) {
   ALLEGRO_EVENT_QUEUE  * self = rbal_eventqueue_unwrap(rself);
   ALLEGRO_EVENT_SOURCE * src  = rbal_eventsource_unwrap(rsrc);
   al_unregister_event_source(self, src);
   return rself;
}

VALUE rbal_eventqueue_empty_p(VALUE rself) {
   ALLEGRO_EVENT_QUEUE  * self = rbal_eventqueue_unwrap(rself);      
   return RBH_INT_BOOL(al_is_event_queue_empty(self));
}

VALUE rbal_eventqueue_poll(VALUE rself) {   
   ALLEGRO_EVENT_QUEUE  * self = rbal_eventqueue_unwrap(rself);
   int ok = 0;
   ALLEGRO_EVENT        * event = rbal_event_alloc();
   
   ok = al_get_next_event(self, event);
   if(!ok) { /* If we didn't get the event, e still have to clean up. */
      rbal_event_free(event); 
      return Qnil;
   }   
   return rbal_event_wrap(event);
}

VALUE rbal_eventqueue_peek(VALUE rself) {   
   ALLEGRO_EVENT_QUEUE  * self = rbal_eventqueue_unwrap(rself);
   int ok = 0;
   ALLEGRO_EVENT        * event = rbal_event_alloc();
   
   ok = al_peek_next_event(self, event);
   if(!ok) { /* If we didn't get the event, e still have to clean up. */
      rbal_event_free(event); 
      return Qnil;
   }   
   return rbal_event_wrap(event);
}

VALUE rbal_eventqueue_flush(VALUE rself) {
   ALLEGRO_EVENT_QUEUE  * self = rbal_eventqueue_unwrap(rself);
   al_flush_event_queue(self);      
   return rself;
}

VALUE rbal_eventqueue_drop(VALUE rself) {
   ALLEGRO_EVENT_QUEUE  * self = rbal_eventqueue_unwrap(rself);      
   return RBH_INT_BOOL(al_drop_next_event(self));
}

/* Only allow the version that leaves the event on the queue. */
VALUE rbal_eventqueue_wait(VALUE rself) {
   ALLEGRO_EVENT_QUEUE  * self = rbal_eventqueue_unwrap(rself);
   al_wait_for_event(self, NULL);       
   return rself;
}

/* Only allow the version that leaves the event on the queue. */
VALUE rbal_eventqueue_wait_timeout(VALUE rself, VALUE rtime) {  
   ALLEGRO_EVENT_QUEUE  * self = rbal_eventqueue_unwrap(rself);
   return RBH_INT_BOOL(al_wait_for_event_timed(self, NULL, RBH_FLOAT(rtime)));
}

void ralleg5_eventsource_init(VALUE mAl) {
  cEventSource = rb_define_class_under(mAl, "EventSource", rb_cObject);
}

void ralleg5_eventqueue_init(VALUE mAl) {
  cEventQueue = rb_define_class_under(mAl, "EventQueue", rb_cObject);
  rb_define_singleton_method(cEventQueue, "new" , rbal_eventqueue_new, 0);
  rb_define_method(cEventQueue, "register"  , rbal_eventqueue_register, 1);
  rb_define_method(cEventQueue, "unregister", rbal_eventqueue_unregister, 1);
  rb_define_method(cEventQueue, "empty?"    , rbal_eventqueue_empty_p, 0);
  rb_define_method(cEventQueue, "poll"      , rbal_eventqueue_poll , 0);
  rb_define_method(cEventQueue, "peek"      , rbal_eventqueue_peek , 0);
  rb_define_method(cEventQueue, "flush"     , rbal_eventqueue_flush, 0);
  rb_define_method(cEventQueue, "drop"      , rbal_eventqueue_drop , 0);
  rb_define_method(cEventQueue, "wait"      , rbal_eventqueue_wait, 0);
  rb_define_method(cEventQueue, "timeout"   , rbal_eventqueue_wait_timeout, 1);
}


void ralleg5_event_init(VALUE mAl) {
  ralleg5_eventsource_init(mAl);
  ralleg5_eventqueue_init(mAl);
  
  cEvent = rb_define_class_under(mAl, "Event", rb_cObject);
  rb_define_const(cEvent, "JOYSTICK_AXIS"
                        , UINT2NUM(ALLEGRO_EVENT_JOYSTICK_AXIS));
  rb_define_const(cEvent, "JOYSTICK_BUTTON_DOWN"
                        , UINT2NUM(ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN));
  rb_define_const(cEvent, "JOYSTICK_BUTTON_UP"
                        , UINT2NUM(ALLEGRO_EVENT_JOYSTICK_BUTTON_UP));
  rb_define_const(cEvent, "JOYSTICK_CONFIGURATION"
                        , UINT2NUM(ALLEGRO_EVENT_JOYSTICK_CONFIGURATION));
  rb_define_const(cEvent, "KEY_DOWN"
                        , UINT2NUM(ALLEGRO_EVENT_KEY_DOWN));
  rb_define_const(cEvent, "KEY_UP"
                        , UINT2NUM(ALLEGRO_EVENT_KEY_UP));
  rb_define_const(cEvent, "KEY_CHAR"
                        , UINT2NUM(ALLEGRO_EVENT_KEY_CHAR));
  rb_define_const(cEvent, "MOUSE_AXES"
                        , UINT2NUM(ALLEGRO_EVENT_MOUSE_AXES));
  rb_define_const(cEvent, "MOUSE_WARPED"
                        , UINT2NUM(ALLEGRO_EVENT_MOUSE_WARPED));
  rb_define_const(cEvent, "MOUSE_BUTTON_UP"
                        , UINT2NUM(ALLEGRO_EVENT_MOUSE_BUTTON_UP));
  rb_define_const(cEvent, "MOUSE_BUTTON_DOWN"
                        , UINT2NUM(ALLEGRO_EVENT_MOUSE_BUTTON_DOWN));
  rb_define_const(cEvent, "MOUSE_ENTER_DISPLAY"
                        , UINT2NUM(ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY));
  rb_define_const(cEvent, "MOUSE_LEAVE_DISPLAY"
                        , UINT2NUM(ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY));
  rb_define_const(cEvent, "TIMER"
                        , UINT2NUM(ALLEGRO_EVENT_TIMER));
  rb_define_const(cEvent, "DISPLAY_EXPOSE"
                        , UINT2NUM(ALLEGRO_EVENT_DISPLAY_EXPOSE));
  rb_define_const(cEvent, "DISPLAY_RESIZE"
                        , UINT2NUM(ALLEGRO_EVENT_DISPLAY_RESIZE));
  rb_define_const(cEvent, "DISPLAY_CLOSE"
                        , UINT2NUM(ALLEGRO_EVENT_DISPLAY_CLOSE));
  rb_define_const(cEvent, "DISPLAY_LOST"
                        , UINT2NUM(ALLEGRO_EVENT_DISPLAY_LOST));
  rb_define_const(cEvent, "DISPLAY_FOUND"
                        , UINT2NUM(ALLEGRO_EVENT_DISPLAY_FOUND));
  rb_define_const(cEvent, "DISPLAY_SWITCH_IN"
                        , UINT2NUM(ALLEGRO_EVENT_DISPLAY_SWITCH_IN));
  rb_define_const(cEvent, "DISPLAY_SWITCH_OUT_"
                        , UINT2NUM(ALLEGRO_EVENT_DISPLAY_SWITCH_OUT));
  rb_define_const(cEvent, "DISPLAY_ORIENTATION"
                        , UINT2NUM(ALLEGRO_EVENT_DISPLAY_ORIENTATION));

  /* rb_define_method(cEvent, , , 0); */
  rb_define_method(cEvent, "type"       , rbal_event_type, 0);
  rb_define_method(cEvent, "display?"   , rbal_event_display_p, 0);
  rb_define_method(cEvent, "display"    , rbal_event_display, 0);
  rb_define_method(cEvent, "joystick?"  , rbal_event_joystick_p, 0);
  rb_define_method(cEvent, "joystick"   , rbal_event_id   , 0);
  rb_define_method(cEvent, "keyboard?"  , rbal_event_keyboard_p, 0);
  rb_define_method(cEvent, "mouse?"     , rbal_event_mouse_p, 0);
  rb_define_method(cEvent, "timer?"     , rbal_event_timer_p, 0);
  
  rb_define_method(cEvent, "x"           , rbal_event_x, 0);
  rb_define_method(cEvent, "y"           , rbal_event_y, 0);
  rb_define_method(cEvent, "z"           , rbal_event_z, 0);
  rb_define_method(cEvent, "dx"          , rbal_event_dx, 0);
  rb_define_method(cEvent, "dy"          , rbal_event_dy, 0);
  rb_define_method(cEvent, "dz"          , rbal_event_dz, 0);
  rb_define_method(cEvent, "button"      , rbal_event_button, 0);
  rb_define_method(cEvent, "width"       , rbal_event_width, 0);
  rb_define_method(cEvent, "height"      , rbal_event_height, 0);
  rb_define_method(cEvent, "orientation" , rbal_event_orientation, 0);
  rb_define_method(cEvent, "stick"       , rbal_event_stick, 0);
  rb_define_method(cEvent, "axis"        , rbal_event_axis , 0);
  rb_define_method(cEvent, "pos"         , rbal_event_pos  , 0);  
  rb_define_method(cEvent, "keycode"     , rbal_event_keycode, 0);
  rb_define_method(cEvent, "unichar"     , rbal_event_unichar, 0);
  rb_define_method(cEvent, "modifiers"   , rbal_event_modifiers, 0);
  rb_define_method(cEvent, "repeat"      , rbal_event_repeat, 0);
  rb_define_method(cEvent, "pressure"    , rbal_event_pressure, 0);
  rb_define_method(cEvent, "count"       , rbal_event_count, 0);
  rb_define_method(cEvent, "error"       , rbal_event_error, 0);
  
}   
