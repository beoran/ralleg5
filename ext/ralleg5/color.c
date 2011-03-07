#include "ralleg5.h"

static VALUE cColor;

ALLEGRO_COLOR * rbal_color_alloc() {
  return calloc(sizeof(ALLEGRO_COLOR),1);
}

ALLEGRO_COLOR * rbal_color_new(ALLEGRO_COLOR tocopy) {
  ALLEGRO_COLOR * result = rbal_color_alloc();
  if(!result) return NULL;
  memcpy(result, &tocopy, sizeof(ALLEGRO_COLOR));
  return result;
}


void rbal_color_free(ALLEGRO_COLOR * self) {
  free(self);
}

VALUE rbal_color_wrap(ALLEGRO_COLOR * ptr) {
   if(!ptr) return Qnil;
   return Data_Wrap_Struct(cColor, 0, rbal_color_free, ptr);
}

ALLEGRO_COLOR * rbal_color_unwrap(VALUE rself) {
  ALLEGRO_COLOR * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_COLOR, result);
  return result;
}

VALUE rbal_color_map_rgb(VALUE rself, VALUE rr, VALUE rg, VALUE rb) {
  ALLEGRO_COLOR * result = NULL;
  result = rbal_color_new(al_map_rgb(RBH_INT(rr), RBH_INT(rb), RBH_INT(rg)));
  if(!result) return Qnil;
  return rbal_color_wrap(result);  
}

VALUE rbal_color_map_rgba(VALUE rself, VALUE rr, VALUE rg, VALUE rb, VALUE ra) {
  ALLEGRO_COLOR * result = NULL;
  ALLEGRO_COLOR aid;
  aid     = al_map_rgba(RBH_INT(rr), RBH_INT(rb), RBH_INT(rg), RBH_INT(ra));
  result  = rbal_color_new(aid);
  if(!result) return Qnil;
  return rbal_color_wrap(result);  
}

VALUE rbal_color_rgba(VALUE rself) {
  unsigned char r = 0, g = 0, b = 0, a = 0;
  ALLEGRO_COLOR * self = rbal_color_unwrap(rself);
  if(!self) return Qnil;
  al_unmap_rgba(*self, &r, &g,&b,  &a);   
  return rb_ary_new3(4, RBH_INT_NUM(r), RBH_INT_NUM(b), 
                        RBH_INT_NUM(g), RBH_INT_NUM(a) );
}  

VALUE rbal_color_rgb(VALUE rself) {
  unsigned char r = 0, g = 0, b = 0, a = 0;
  ALLEGRO_COLOR * self = rbal_color_unwrap(rself);
  if(!self) return Qnil;
  al_unmap_rgb(*self, &r, &g,&b);   
  return rb_ary_new3(3, RBH_INT_NUM(r), RBH_INT_NUM(b), 
                        RBH_INT_NUM(g));
}  


void ralleg5_color_init(VALUE mAl) {
  cColor = rb_define_class_under(mAl, "Color", rb_cObject);
  rb_define_singleton_method(cColor, "rgb"  , rbal_color_map_rgb  , 3);
  rb_define_singleton_method(cColor, "rgba" , rbal_color_map_rgba , 4);   
  rb_define_method(cColor, "rgba" , rbal_color_rgba , 0);
  rb_define_method(cColor, "rgb" , rbal_color_rgb   , 0);
}

