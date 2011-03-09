#include "ralleg5.h"

VALUE cTransform;

/* Allocates a transform */
ALLEGRO_TRANSFORM * rbal_transform_alloc() {
  return al_calloc(sizeof(ALLEGRO_TRANSFORM), 1);
}

/* Frees a transform */
void rbal_transform_free(ALLEGRO_TRANSFORM * ptr) {
  return al_free(ptr);
}

/* Wraps a transform into a Ruby object, optionally garbage collected. */
VALUE rbal_transform_wrap(ALLEGRO_TRANSFORM * ptr, int gc) {
  if(!ptr) return Qnil;
  if (gc == RBAL_GC) {
    return Data_Wrap_Struct(cTransform, 0, rbal_transform_free, ptr);
  } else {
    return Data_Wrap_Struct(cTransform, 0, 0, ptr);
  } 
}


/* Unwraps transform a from a Ruby object */
ALLEGRO_TRANSFORM  * rbal_transform_unwrap(VALUE rself) { 
  ALLEGRO_TRANSFORM * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_TRANSFORM, result);
  return result;
}

/* OOP read access to the transform's elements. */
VALUE rbal_transform_get(VALUE rtrans, VALUE ri, VALUE rj) {
  ALLEGRO_TRANSFORM * trans = rbal_transform_unwrap(rtrans);
  int i			    = RBH_INT(ri);
  int j			    = RBH_INT(rj);
  if((!trans) || (i < 0) || (j>0) || (i > 3) || (j>3)) return Qnil;
  return RBH_FLOAT_NUM(trans->m[i][j]);  
}

/* OOP write access to the transform's elements. */
VALUE rbal_transform_set(VALUE rtrans, VALUE ri, VALUE rj, VALUE rval) {
  ALLEGRO_TRANSFORM * trans = rbal_transform_unwrap(rtrans);
  int i			    = RBH_INT(ri);
  int j			    = RBH_INT(rj);
  if((!trans) || (i < 0) || (j>0) || (i > 3) || (j>3)) return Qnil;
  trans->m[i][j]            = RBH_FLOAT(rval);
  return RBH_FLOAT_NUM(trans->m[i][j]);  
}


VALUE rbal_create_transform(VALUE r_) {
  ALLEGRO_TRANSFORM * trans = rbal_transform_alloc();
  al_identity_transform(trans);
  return al_transform_wrap(trans, RBAL_NO_GC);
}

VALUE rbal_transform_new(VALUE r_) {
  ALLEGRO_TRANSFORM * trans = rbal_transform_alloc();
  al_identity_transform(trans);
  return al_transform_wrap(trans, RBAL_GC);
}

VALUE rbal_destroy_transform(VALUE r_, VALUE rtrans) {
  ALLEGRO_TRANSFORM * trans = rbal_transform_unwrap(rtrans);
  al_transform_free(trans);
  return r_;
}

VALUE rbal_use_transform(VALUE r_, VALUE rtrans) {
  ALLEGRO_TRANSFORM * trans = rbal_transform_unwrap(rtrans);
  al_use_transform(trans);
  return rtrans;
}

VALUE rbal_copy_transform(VALUE r_, VALUE rdst, VALUE rsrc) {
  ALLEGRO_TRANSFORM * src = rbal_transform_unwrap(rdst);
  ALLEGRO_TRANSFORM * dst = rbal_transform_unwrap(rsrc);
  al_copy_transform(dst, src);
  return rdst;
}

VALUE rbal_identity_transform(VALUE r_, VALUE rtrans) {
  ALLEGRO_TRANSFORM * trans = rbal_transform_unwrap(rtrans);
  al_identity_transform(trans);
  return rtrans;
}

VALUE rbal_build_transform(VALUE r_, VALUE rtrans, VALUE rx, 
			   VALUE ry, VALUE rsx, VALUE rsy, VALUE rtheta) {
  ALLEGRO_TRANSFORM * trans = rbal_transform_unwrap(rtrans);
  float 	          x = RBH_FLOAT(rx);
  float 	          y = RBH_FLOAT(ry);
  float 	         sx = RBH_FLOAT(rsx);
  float 	         sy = RBH_FLOAT(rsy);
  float 	      theta = RBH_FLOAT(rtheta);  
  al_build_transform(trans, rx, ry, rsx, rsy, rtheta);
  return rtrans;
}

VALUE rbal_translate_transform(VALUE r_, VALUE rtrans, VALUE rx, VALUE ry) {
  ALLEGRO_TRANSFORM * trans = rbal_transform_unwrap(rtrans);
  float 	          x = RBH_FLOAT(rx);
  float 	          y = RBH_FLOAT(ry);  
  al_translate_transform(trans, rx, ry);
  return rtrans;
}

VALUE rbal_rotate_transform(VALUE r_, VALUE rtrans, VALUE rtheta) {
  ALLEGRO_TRANSFORM * trans = rbal_transform_unwrap(rtrans);
  float 	      theta = RBH_FLOAT(rtheta);  
  al_rotate_transform(trans, rtheta);
  return rtrans;
}

VALUE rbal_scale_transform(VALUE r_, VALUE rtrans, VALUE rsx, VALUE rsy) {
  ALLEGRO_TRANSFORM * trans = rbal_transform_unwrap(rtrans);
  float 	         sx = RBH_FLOAT(rsx);
  float 	         sy = RBH_FLOAT(rsy);
  al_scale_transform(trans, rsx, rsy);
  return rtrans;
}

VALUE rbal_compose_transform(VALUE r_, VALUE rtrans, VALUE rother) {
  ALLEGRO_TRANSFORM * trans = rbal_transform_unwrap(rtrans);
  ALLEGRO_TRANSFORM * other = rbal_transform_unwrap(rother);
  al_compose_transform(trans, other);
  return rtrans;
}

VALUE rbal_get_current_transform(VALUE r_) {
  ALLEGRO_TRANSFORM * trans = (ALLEGRO_TRANSFORM *) al_get_current_transform();
  return rbal_transform_wrap(trans, RBAL_NO_GC);
}

VALUE rbal_invert_transform(VALUE r_, VALUE rtrans) {
  ALLEGRO_TRANSFORM * trans = rbal_transform_unwrap(rtrans);
  al_invert_transform(trans);
  return rtrans;
}


VALUE rbal_check_inverse(VALUE r_, VALUE rtrans, VALUE rtol) {
  ALLEGRO_TRANSFORM * trans = rbal_transform_unwrap(rtrans);
  float 	        tol = RBH_FLOAT(rtol); 
  return RBH_INT_BOOL(al_check_inverse(trans, RBH_FLOAT(tol)));
}

VALUE rbal_transform_coordinates(VALUE r_, VALUE rtrans, VALUE rx, VALUE ry) {
  ALLEGRO_TRANSFORM * trans = rbal_transform_unwrap(rtrans);
  float 	          x = RBH_FLOAT(rx);
  float 	          y = RBH_FLOAT(ry); 
  al_transform_coordinates(trans, &x, &y);
  return rb_ary_new3(2, RBH_INT_NUM(x), RBH_INT_NUM(y));
}  


void ralleg5_transform_init(VALUE mAl, VALUE mLow) {
  cTransform = rb_define_class_under(mAl, "Transform" , rb_cObject);
  rb_define_singleton_method(cTransform, "new"	      , rbal_transform_new, 0);
  rb_define_singleton_method(cTransform, "get"	      , rbal_transform_get, 2);
  rb_define_singleton_method(cTransform, "set"	      , rbal_transform_set, 3);
  
  rbal_low_func(mLow  , al_create_transform             , 0 );
  rbal_low_func(mLow  , al_destroy_transform            , 1 );
  rbal_low_func(mLow  , al_identity_transform           , 1 );
  rbal_low_func(mLow  , al_use_transform           	, 1 );
  rbal_low_func(mLow  , al_copy_transform           	, 2 );
  rbal_low_func(mLow  , al_build_transform           	, 6 );
  rbal_low_func(mLow  , al_translate_transform        	, 3 );
  rbal_low_func(mLow  , al_rotate_transform           	, 2 );
  rbal_low_func(mLow  , al_scale_transform           	, 3 );
  rbal_low_func(mLow  , al_compose_transform           	, 2 );
  rbal_low_func(mLow  , al_transform_coordinates       	, 3 );
  rbal_low_func(mLow  , al_get_current_transform      	, 0 );
  rbal_low_func(mLow  , al_invert_transform     	, 1 );
  rbal_low_func(mLow  , al_check_inverse      		, 2 );
  
}

 
 


