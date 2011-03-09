#include "ralleg5.h"

VALUE cTransform;

// Wraps a transform into a Ruby object, optionally garbage collected. 
VALUE rbal_transform_wrap(ALLEGRO_TRANSFORM * ptr, int gc) {
  if(!ptr) return Qnil;
  if (gc == RBAL_GC) {
    return Data_Wrap_Struct(cTransform, 0, free, ptr);
  } else {
    return Data_Wrap_Struct(cTransform, 0, 0, ptr);
  } 
}

// Unwraps transform a from a Ruby object 
ALLEGRO_TRANSFORM  * rbal_transform_unwrap(VALUE rself) { 
  ALLEGRO_TRANSFORM * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_TRANSFORM, result);
  return result;
}

VALUE rbal_use_transform(VALUE r_, VALUE rtrans) {
  ALLEGRO_TRANSFORM * trans = rbal_transform_unwrap(rtrans);
  al_use_transform(trans);
  return r_;
}

VALUE rbal_copy_transform(VALUE r_, VALUE rdst, VALUE rsrc) {
  ALLEGRO_TRANSFORM * src = rbal_transform_unwrap(rdst);
  ALLEGRO_TRANSFORM * dst = rbal_transform_unwrap(rsrc);
  al_copy_transform(dst, src);
  return r_;
}


/* Transformations*/
AL_FUNC(void, al_use_transform, (const ALLEGRO_TRANSFORM* trans));
AL_FUNC(void, al_copy_transform, (ALLEGRO_TRANSFORM* dest, const ALLEGRO_TRANSFORM* src));
AL_FUNC(void, al_identity_transform, (ALLEGRO_TRANSFORM* trans));
AL_FUNC(void, al_build_transform, (ALLEGRO_TRANSFORM* trans, float x, float y, float sx, float sy, float theta));
AL_FUNC(void, al_translate_transform, (ALLEGRO_TRANSFORM* trans, float x, float y));
AL_FUNC(void, al_rotate_transform, (ALLEGRO_TRANSFORM* trans, float theta));
AL_FUNC(void, al_scale_transform, (ALLEGRO_TRANSFORM* trans, float sx, float sy));
AL_FUNC(void, al_transform_coordinates, (const ALLEGRO_TRANSFORM* trans, float* x, float* y));
AL_FUNC(void, al_compose_transform, (ALLEGRO_TRANSFORM* trans, const ALLEGRO_TRANSFORM* other));
AL_FUNC(const ALLEGRO_TRANSFORM*, al_get_current_transform, (void));
AL_FUNC(void, al_invert_transform, (ALLEGRO_TRANSFORM *trans));
AL_FUNC(int, al_check_inverse, (const ALLEGRO_TRANSFORM *trans, float tol));

