#include "ralleg5.h"

/* Ruby already has oodles of I18n and strings encodings, 
so only the bare neccesities of the ALLEGRO_USTR are wrapped. */

VALUE cUstr;


/* Wraps an ustr into a Ruby object, optionally garbage collected. */
VALUE rbal_ustr_wrap(ALLEGRO_USTR * ptr, int gc) {
  if(!ptr) return Qnil;
  if (gc) {
    return Data_Wrap_Struct(cUstr, 0, al_ustr_free, ptr);
  } else {
    return Data_Wrap_Struct(cUstr, 0, 0, ptr);
  } 
}

/* Unwraps a ustr */
ALLEGRO_USTR * rbal_ustr_unwrap(VALUE rself) { 
  ALLEGRO_USTR * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_USTR, result);
  return result;
}

/* Transforms a ruby string value that as han UTF-8 encoding to
* a newly allocated allegro ustr. Must be freed with rbal_ustr_free.
*/
ALLEGRO_USTR * rbal_rbstr_ustr(VALUE rstr) {
  size_t       size = RBH_CSTRLEN(rstr);
  const char * str  = RBH_CSTR(rstr);
  return al_ustr_new_from_buffer(str, size); 
}


/* Low level API. */
VALUE rbal_ustr_new(VALUE r_, VALUE rstr) {
  return rbal_ustr_wrap(rbal_rbstr_ustr(rstr), RBAL_NO_GC);
}

VALUE rbal_ustr_free(VALUE r_, VALUE rustr) {
  ALLEGRO_USTR * ustr = rbal_ustr_unwrap(rustr);
  al_ustr_free(ustr);
  return r_;
}

/* High level API. */
VALUE rbal_ustr_new_high(VALUE r_, VALUE rstr) {
  return rbal_ustr_wrap(rbal_rbstr_ustr(rstr), RBAL_GC);
}



void ralleg5_ustr_init(VALUE mAl, VALUE mLow) {
  cUstr           = rb_define_class_under(mAl, "Ustr", rb_cObject);  
  /* High level API, to be enhanced using Ruby libs. */
  rb_define_singleton_method(cUstr        , "new" , rbal_ustr_new_high, 1);
  
  
  /* Low level API */
  
  rbal_low_func(mLow, al_ustr_new            , 1);
  rbal_low_func(mLow, al_ustr_free           , 1);
  
}



