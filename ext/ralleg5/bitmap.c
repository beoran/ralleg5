#include "ralleg5.h"


static VALUE cLock;

void rbal_lock_free(ALLEGRO_LOCKED_REGION * ptr) {
  free(ptr);
}

ALLEGRO_LOCKED_REGION * rbal_lock_alloc() {
  return calloc(sizeof(ALLEGRO_LOCKED_REGION), 1);
}

VALUE rbal_lock_wrap(ALLEGRO_LOCKED_REGION * ptr) {
   if(!ptr) return Qnil;
   // Locks are managed by Allegro, so Ruby doens't need to erase them.
   return Data_Wrap_Struct(cLock, 0, 0, ptr);
}

ALLEGRO_LOCKED_REGION * rbal_lock_unwrap(VALUE rself) {
  ALLEGRO_LOCKED_REGION * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_LOCKED_REGION, result);
  return result;
}

VALUE rbal_lock_format(VALUE rself) {
  ALLEGRO_LOCKED_REGION * self = rbal_lock_unwrap(rself);
  if(!self) return Qnil;
  return RBH_INT_NUM(self->format);
}

VALUE rbal_lock_pitch(VALUE rself) {
  ALLEGRO_LOCKED_REGION * self = rbal_lock_unwrap(rself);
  if(!self) return Qnil;
  return RBH_INT_NUM(self->pitch);
}

VALUE rbal_lock_pixel_size(VALUE rself) {
  ALLEGRO_LOCKED_REGION * self = rbal_lock_unwrap(rself);
  if(!self) return Qnil;
  return RBH_INT_NUM(self->pixel_size);
}


void ralleg5_lock_init(VALUE mAl) {
  cLock = rb_define_class_under(mAl, "Lock", rb_cObject);
  rb_define_method(cLock, "format"       , rbal_lock_format	, 0);
  rb_define_method(cLock, "pitch"        , rbal_lock_pitch	, 0);
  rb_define_method(cLock, "pixelsize"    , rbal_lock_pixel_size	, 0);
}  




static VALUE cBitmap;


VALUE rbal_bitmap_wrap(ALLEGRO_BITMAP * ptr) {
   if(!ptr) return Qnil;
   return Data_Wrap_Struct(cBitmap, 0, al_destroy_bitmap, ptr);
}


ALLEGRO_BITMAP * rbal_bitmap_unwrap(VALUE rself) {
  ALLEGRO_BITMAP * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_BITMAP, result);
  return result;
}

VALUE rbal_new_bitmap_format(VALUE self) {
  return RBH_INT_NUM(al_get_new_bitmap_format());
}

VALUE rbal_new_bitmap_flags(VALUE self) {
return RBH_INT_NUM(al_get_new_bitmap_flags());
}


VALUE rbal_new_bitmap_format_(VALUE self, VALUE rformat) {
  al_set_new_bitmap_format(RBH_INT(rformat));
  return rbal_new_bitmap_format(self);
}

VALUE rbal_new_bitmap_flags_(VALUE self, VALUE rflags) {
  al_set_new_bitmap_flags(RBH_INT(rflags));
  return rbal_new_bitmap_flags(self);
}

/* TODO: al_add_new_bitmap_flag ??? */ 

VALUE rbal_bitmap_new(VALUE rself, VALUE rw, VALUE rh) {
  return rbal_bitmap_wrap(al_create_bitmap(RBH_INT(rw), RBH_INT(rh)));
}


VALUE rbal_bitmap_width(VALUE rself) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  return RBH_INT_NUM(al_get_bitmap_width(self));
}

VALUE rbal_bitmap_height(VALUE rself) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  return RBH_INT_NUM(al_get_bitmap_height(self));
}

VALUE rbal_bitmap_format(VALUE rself) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  return RBH_INT_NUM(al_get_bitmap_format(self));
}

VALUE rbal_bitmap_flags(VALUE rself) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  return RBH_INT_NUM(al_get_bitmap_flags(self));
}

/* Blitting */
VALUE rbal_bitmap_draw(VALUE rself, VALUE rdx, VALUE rdy, VALUE flags) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  al_draw_bitmap(self, RBH_FLOAT(rdx), RBH_FLOAT(rdy), RBH_INT(flags));
  return Qtrue;
} 

VALUE rbal_bitmap_draw_region(VALUE rself, 
  VALUE rsx, VALUE rsy, VALUE rsw, VALUE rsh,
  VALUE rdx, VALUE rdy, VALUE flags) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  al_draw_bitmap_region(self, RBH_FLOAT(rsx), RBH_FLOAT(rsy), 
                       RBH_FLOAT(rsw), RBH_FLOAT(rsh),
                       RBH_FLOAT(rdx), RBH_FLOAT(rdy), RBH_INT(flags));
  return Qtrue;
} 


VALUE rbal_bitmap_draw_scaled(VALUE rself, 
  VALUE rsx, VALUE rsy, VALUE rsw, VALUE rsh,
  VALUE rdx, VALUE rdy, VALUE rdw, VALUE rdh,  VALUE flags) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  al_draw_scaled_bitmap(self, RBH_FLOAT(rsx), RBH_FLOAT(rsy), 
                       RBH_FLOAT(rsw), RBH_FLOAT(rsh),                       
                       RBH_FLOAT(rdx), RBH_FLOAT(rdy),
                       RBH_FLOAT(rdw), RBH_FLOAT(rdh),
                       RBH_INT(flags));
  return Qtrue;
} 

VALUE rbal_bitmap_draw_rotated(VALUE rself, 
  VALUE rcx, VALUE rcy, 
  VALUE rdx, VALUE rdy, VALUE angle, VALUE flags) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  al_draw_rotated_bitmap(self, 
  RBH_FLOAT(rcx), RBH_FLOAT(rcy),
  RBH_FLOAT(rdx), RBH_FLOAT(rdy), 
  RBH_FLOAT(angle), RBH_INT(flags));
  return Qtrue;
} 

/** Rotate and scale = zoom */
VALUE rbal_bitmap_draw_zoom(VALUE rself, 
  VALUE rcx, VALUE rcy, 
  VALUE rdx, VALUE rdy, 
  VALUE rxs, VALUE rys,
  VALUE angle, VALUE flags) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  al_draw_scaled_rotated_bitmaparotated_bitmap(self, 
  RBH_FLOAT(rcx), RBH_FLOAT(rcy),
  RBH_FLOAT(rdx), RBH_FLOAT(rdy),
  RBH_FLOAT(rxs), RBH_FLOAT(rys),
  RBH_FLOAT(angle), RBH_INT(flags));
  return Qtrue;
} 

/* Tinted blitting */
VALUE rbal_bitmap_tint(VALUE rself, VALUE rcolor, VALUE rdx, VALUE rdy, VALUE flags) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  ALLEGRO_COLOR    tint = rbal_color_struct(rcolor);
  al_draw_tinted_bitmap(self, tint, 
                        RBH_FLOAT(rdx), RBH_FLOAT(rdy), RBH_INT(flags));
  return Qtrue;
} 

VALUE rbal_bitmap_tint_region(VALUE rself, VALUE rcolor, 
  VALUE rsx, VALUE rsy, VALUE rsw, VALUE rsh,
  VALUE rdx, VALUE rdy, VALUE flags) {  
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  ALLEGRO_COLOR    tint = rbal_color_struct(rcolor);
  al_draw_tinted_bitmap_region(self, tint, RBH_FLOAT(rsx), RBH_FLOAT(rsy), 
                       RBH_FLOAT(rsw), RBH_FLOAT(rsh),
                       RBH_FLOAT(rdx), RBH_FLOAT(rdy), RBH_INT(flags));
  return Qtrue;
} 


VALUE rbal_bitmap_tint_scaled(VALUE rself, VALUE rcolor, 
  VALUE rsx, VALUE rsy, VALUE rsw, VALUE rsh,
  VALUE rdx, VALUE rdy, VALUE rdw, VALUE rdh,  VALUE flags) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  ALLEGRO_COLOR    tint = rbal_color_struct(rcolor);
  al_draw_tinted_scaled_bitmap(self, tint, RBH_FLOAT(rsx), RBH_FLOAT(rsy), 
                       RBH_FLOAT(rsw), RBH_FLOAT(rsh),                       
                       RBH_FLOAT(rdx), RBH_FLOAT(rdy),
                       RBH_FLOAT(rdw), RBH_FLOAT(rdh),
                       RBH_INT(flags));
  return Qtrue;
} 

VALUE rbal_bitmap_tint_rotated(VALUE rself, VALUE rcolor,
  VALUE rcx, VALUE rcy, 
  VALUE rdx, VALUE rdy, VALUE angle, VALUE flags) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  ALLEGRO_COLOR    tint = rbal_color_struct(rcolor);
  al_draw_tinted_rotated_bitmap(self, tint,
  RBH_FLOAT(rcx), RBH_FLOAT(rcy),
  RBH_FLOAT(rdx), RBH_FLOAT(rdy), 
  RBH_FLOAT(angle), RBH_INT(flags));
  return Qtrue;
} 


VALUE rbal_bitmap_tint_zoom(VALUE rself, VALUE rcolor,
  VALUE rcx, VALUE rcy, 
  VALUE rdx, VALUE rdy, 
  VALUE rxs, VALUE rys,
  VALUE angle, VALUE flags) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  ALLEGRO_COLOR    tint = rbal_color_struct(rcolor);
  al_draw_tinted_scaled_rotated_bitmap(self, tint, 
  RBH_FLOAT(rcx), RBH_FLOAT(rcy),
  RBH_FLOAT(rdx), RBH_FLOAT(rdy),
  RBH_FLOAT(rxs), RBH_FLOAT(rys),
  RBH_FLOAT(angle), RBH_INT(flags));
  return Qtrue;
} 

VALUE rbal_put_pixel(VALUE rself, VALUE rx, VALUE ry, VALUE rcolor) {
  ALLEGRO_COLOR  tint = rbal_color_struct(rcolor);
  al_put_pixel(RBH_INT(rx), RBH_INT(ry), tint);  
  return Qtrue;
}

VALUE rbal_blend_pixel(VALUE rself, VALUE rx, VALUE ry, VALUE rcolor) {
  ALLEGRO_COLOR  tint = rbal_color_struct(rcolor);
  al_put_blended_pixel(RBH_INT(rx), RBH_INT(ry), tint);  
  return Qtrue;
}

VALUE rbal_get_pixel(VALUE rself, VALUE rx, VALUE ry) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  return rbal_color_wrapstruct(al_get_pixel(self, RBH_INT(rx), RBH_INT(ry)));  
}

VALUE rbal_get_pixel_size(VALUE rself, VALUE rformat) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  return RBH_INT_NUM(al_get_pixel_size(RBH_INT(rformat)));  
}


VALUE rbal_bitmap_mask(VALUE rself, VALUE rcolor) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  ALLEGRO_COLOR    mask = rbal_color_struct(rcolor);
  al_convert_mask_to_alpha(self, mask);
  return Qtrue;
} 

/* Clipping */

VALUE rbal_bitmap_getclip(VALUE rself) {
  int x = 0, y = 0, w = 0, h = 0;
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  al_get_clipping_rectangle(&x, &y, &w, &h);
  return rb_ary_new3(4, RBH_INT_NUM(x), RBH_INT_NUM(y),
                        RBH_INT_NUM(w), RBH_INT_NUM(h));
} 

VALUE rbal_bitmap_setclip(VALUE rself, 
                          VALUE rx, VALUE ry, VALUE rw, VALUE rh) {
  al_set_clipping_rectangle(RBH_INT(rx), RBH_INT(ry), 
                            RBH_INT(rw), RBH_INT(rh));
  return Qtrue;
} 

/* Sub bitmaps */

VALUE rbal_bitmap_sub_p(VALUE rself) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  return RBH_INT_BOOL(al_is_sub_bitmap(self));
} 

VALUE rbal_bitmap_sub(VALUE rself, VALUE rx, VALUE ry, VALUE rw, VALUE rh) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  ALLEGRO_BITMAP * new  = 
  al_create_sub_bitmap(self, RBH_INT(rx), RBH_INT(ry), 
                              RBH_INT(rw), RBH_INT(rh));
  return rbal_bitmap_wrap(new);
} 

/* Miscellaneous */
VALUE rbal_bitmap_clone(VALUE rself) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  ALLEGRO_BITMAP * new  = al_clone_bitmap(self);
  return rbal_bitmap_wrap(new);
} 

VALUE rbal_bitmap_lock_p(VALUE rself) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  return RBH_INT_BOOL(al_is_bitmap_locked(self));
} 

VALUE rbal_set_blender(VALUE rself, VALUE rop, VALUE rsource, VALUE rdest) {
  al_set_blender(RBH_INT(rop), RBH_INT(rsource), RBH_INT(rdest));
  return rself;
}

VALUE rbal_get_blender(VALUE rself) {
  int op = 0, source = 0, dest = 0;   
  al_get_blender(&op, &source, &dest);
  return rb_ary_new3(3, RBH_INT_NUM(op), RBH_INT_NUM(source),
                        RBH_INT_NUM(dest));
}

VALUE rbal_set_separate_blender(VALUE rself, 
VALUE rop, VALUE rsource, VALUE rdest, 
VALUE ropa, VALUE rsourcea, VALUE rdesta) {
  al_set_separate_blender(RBH_INT(rop), RBH_INT(rsource), RBH_INT(rdest),
  RBH_INT(ropa), RBH_INT(rsourcea), RBH_INT(rdesta));
  return rself;
}

VALUE rbal_get_separate_blender(VALUE rself) {
  int op = 0, source = 0, dest = 0, opa = 0, sourcea = 0, desta = 0;   
  al_get_separate_blender(&op, &source, &dest, 
  &opa, &sourcea, &desta);
  return rb_ary_new3(6, RBH_INT_NUM(op), RBH_INT_NUM(source),
                        RBH_INT_NUM(dest), 
                        RBH_INT_NUM(opa), RBH_INT_NUM(sourcea),
                        RBH_INT_NUM(desta)
                        );
}


/* Locking */

VALUE rbal_bitmap_lock(VALUE rself, VALUE rformat, VALUE rflags) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  ALLEGRO_LOCKED_REGION * result = NULL;
  result = al_lock_bitmap(self, RBH_INT(rformat), RBH_INT(rflags));
  return rbal_lock_wrap(result);  
}

VALUE rbal_bitmap_lock_region(VALUE rself, VALUE rx, VALUE ry, VALUE rw, VALUE rh, VALUE rformat, VALUE rflags) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);
  ALLEGRO_LOCKED_REGION * result = NULL;
  result = al_lock_bitmap_region(self,  RBH_INT(rx), RBH_INT(ry), 
                                 RBH_INT(rw), RBH_INT(rh),
                                 RBH_INT(rformat), RBH_INT(rflags));
  return rbal_lock_wrap(result);  
}

VALUE rbal_bitmap_unlock(VALUE rself) {
  ALLEGRO_BITMAP * self = rbal_bitmap_unwrap(rself);  
  al_unlock_bitmap(self);
  return rself;  
}


AL_FUNC(void, al_unlock_bitmap, (ALLEGRO_BITMAP *bitmap));



void ralleg5_bitmap_init(VALUE mAl) {
  ralleg5_lock_init(mAl);
  cBitmap = rb_define_class_under(mAl, "Bitmap", rb_cObject);
  rb_define_const(cBitmap, "FORMAT_ANY"
                         ,  UINT2NUM(ALLEGRO_PIXEL_FORMAT_ANY));
  rb_define_const(cBitmap, "FORMAT_ANY_NO_ALPHA"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_ANY_NO_ALPHA));
  rb_define_const(cBitmap, "FORMAT_ANY_WITH_ALPHA"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_ANY_WITH_ALPHA));
  
  rb_define_const(cBitmap, "FORMAT_ANY_15_NO_ALPHA"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_ANY_15_NO_ALPHA));
  rb_define_const(cBitmap, "FORMAT_ANY_16_NO_ALPHA"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_ANY_16_NO_ALPHA));
  rb_define_const(cBitmap, "FORMAT_ANY_16_WITH_ALPHA"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_ANY_16_WITH_ALPHA));
  rb_define_const(cBitmap, "FORMAT_ANY_24_NO_ALPHA"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_ANY_24_NO_ALPHA));
  rb_define_const(cBitmap, "FORMAT_ANY_32_NO_ALPHA"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_ANY_32_NO_ALPHA));
  rb_define_const(cBitmap, "FORMAT_ANY_32_WITH_ALPHA"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_ANY_32_WITH_ALPHA));
                         
                             
  rb_define_const(cBitmap, "FORMAT_ARGB_8888"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_ARGB_8888));
  rb_define_const(cBitmap, "FORMAT_ARGB_4444"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_ARGB_4444));
  rb_define_const(cBitmap, "FORMAT_ARGB_1555"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_ARGB_1555));
  rb_define_const(cBitmap, "FORMAT_RGBA_8888"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_RGBA_8888));
  rb_define_const(cBitmap, "FORMAT_RGBA_4444"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_RGBA_4444));
  rb_define_const(cBitmap, "FORMAT_RGBA_5551"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_RGBA_5551));
  rb_define_const(cBitmap, "FORMAT_RGB_888"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_RGB_888));
  rb_define_const(cBitmap, "FORMAT_RGB_565"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_RGB_565));
  rb_define_const(cBitmap, "FORMAT_RGB_555"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_RGB_555));
  rb_define_const(cBitmap, "FORMAT_ABGR_8888"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_ABGR_8888));
  rb_define_const(cBitmap, "FORMAT_ABGR_F32"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_ABGR_F32));
  rb_define_const(cBitmap, "FORMAT_ABGR_8888_LE"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_ABGR_8888_LE));
  rb_define_const(cBitmap, "FORMAT_XBGR_8888"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_XBGR_8888));
  rb_define_const(cBitmap, "FORMAT_BGR_565"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_BGR_565));
  rb_define_const(cBitmap, "FORMAT_BGR_555"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_BGR_555));
  rb_define_const(cBitmap, "FORMAT_BGR_888"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_BGR_888));
  rb_define_const(cBitmap, "FORMAT_RGBX_8888"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_RGBX_8888));
  rb_define_const(cBitmap, "FORMAT_XRGB_8888"
                         , UINT2NUM(ALLEGRO_PIXEL_FORMAT_XRGB_8888));
                         
  rb_define_const(cBitmap, "MEMORY_BITMAP"
                         , UINT2NUM(ALLEGRO_MEMORY_BITMAP));
  rb_define_const(cBitmap, "KEEP_BITMAP_FORMAT"
                         , UINT2NUM(ALLEGRO_KEEP_BITMAP_FORMAT));
  rb_define_const(cBitmap, "FORCE_LOCKING"
                         , UINT2NUM(ALLEGRO_FORCE_LOCKING));
  rb_define_const(cBitmap, "NO_PRESERVE_TEXTURE"
                         , UINT2NUM(ALLEGRO_NO_PRESERVE_TEXTURE));
  rb_define_const(cBitmap, "ALPHA_TEST"
                         , UINT2NUM(ALLEGRO_ALPHA_TEST));
  rb_define_const(cBitmap, "MIN_LINEAR"
                         , UINT2NUM(ALLEGRO_MIN_LINEAR));         
  rb_define_const(cBitmap, "MAG_LINEAR"
                         , UINT2NUM(ALLEGRO_MAG_LINEAR));
  rb_define_const(cBitmap, "MIPMAP"
                         , UINT2NUM(ALLEGRO_MIPMAP));
  rb_define_const(cBitmap, "NO_PREMULTIPLIED_ALPHA"
                         , UINT2NUM(ALLEGRO_NO_PREMULTIPLIED_ALPHA));
  rb_define_const(cBitmap, "VIDEO_BITMAP"
                         , UINT2NUM(ALLEGRO_VIDEO_BITMAP));
  rb_define_const(cBitmap, "FLIP_HORIZONTAL"
                         , UINT2NUM(ALLEGRO_FLIP_HORIZONTAL));
  rb_define_const(cBitmap, "FLIP_VERTICAL"
                         , UINT2NUM(ALLEGRO_FLIP_VERTICAL));
                         
  rb_define_const(cBitmap, "LOCK_READWRITE"
                         , UINT2NUM(ALLEGRO_LOCK_READWRITE));  
  rb_define_const(cBitmap, "LOCK_READONLY"
                         , UINT2NUM(ALLEGRO_LOCK_READONLY));
  rb_define_const(cBitmap, "LOCK_WRITEONLY"
                         , UINT2NUM(ALLEGRO_LOCK_WRITEONLY));
                         
  rb_define_const(cBitmap, "ZERO"
                         , UINT2NUM(ALLEGRO_ZERO));
  rb_define_const(cBitmap, "ONE"
                         , UINT2NUM(ALLEGRO_ONE));
  rb_define_const(cBitmap, "ALPHA"
                         , UINT2NUM(ALLEGRO_ALPHA));
  rb_define_const(cBitmap, "INVERSE_ALPHA"
                         , UINT2NUM(ALLEGRO_INVERSE_ALPHA));
  
  rb_define_const(cBitmap, "ADD"
                         , UINT2NUM(ALLEGRO_ADD));
  rb_define_const(cBitmap, "SRC_MINUS_DEST"
                         , UINT2NUM(ALLEGRO_SRC_MINUS_DEST));
  rb_define_const(cBitmap, "DESR_MINUS_SRC"
                         , UINT2NUM(ALLEGRO_DEST_MINUS_SRC));
  
  rb_define_singleton_method(cBitmap, "new"     , rbal_bitmap_new,  2);
  rb_define_singleton_method(cBitmap, "flags"   , rbal_new_bitmap_flags, 0);
  rb_define_singleton_method(cBitmap, "flags="  , rbal_new_bitmap_flags_, 1);
  rb_define_singleton_method(cBitmap, "format"  , rbal_new_bitmap_format, 0);
  rb_define_singleton_method(cBitmap, "format=" , rbal_new_bitmap_format_, 1);
  
  
  rb_define_method(cBitmap, "width"   , rbal_bitmap_width  , 0);
  rb_define_method(cBitmap, "height"  , rbal_bitmap_height , 0);
  rb_define_method(cBitmap, "format"  , rbal_bitmap_format , 0);
  rb_define_method(cBitmap, "flags"   , rbal_bitmap_flags  , 0);
  rb_define_method(cBitmap, "draw"    , rbal_bitmap_draw        , 3);
  rb_define_method(cBitmap, "rotate"  , rbal_bitmap_draw_rotated, 6);
  rb_define_method(cBitmap, "zoom"    , rbal_bitmap_draw_zoom   , 8);
  rb_define_method(cBitmap, "scale"   , rbal_bitmap_draw_scaled , 9);
  rb_define_method(cBitmap, "tint"    , rbal_bitmap_tint        , 4);
  rb_define_method(cBitmap, "tint_rotate", rbal_bitmap_tint_rotated, 7);
  rb_define_method(cBitmap, "tint_zoom"  , rbal_bitmap_tint_zoom   , 9);
  rb_define_method(cBitmap, "tint_scale" , rbal_bitmap_tint_scaled , 10);
  
  rb_define_singleton_method(cBitmap, "put"  , rbal_put_pixel, 3);
  rb_define_singleton_method(cBitmap, "blend", rbal_blend_pixel, 3);
  rb_define_singleton_method(cBitmap, "pixelsize", rbal_get_pixel_size, 1);
  rb_define_method(cBitmap, "get", rbal_get_pixel, 3);
  rb_define_method(cBitmap, "mask", rbal_bitmap_mask, 1);
  rb_define_singleton_method(cBitmap, "clip", rbal_bitmap_getclip, 0);
  rb_define_singleton_method(cBitmap, "setclip", rbal_bitmap_setclip, 4);  
    
  rb_define_method(cBitmap, "sub?"  , rbal_bitmap_sub_p, 0);
  rb_define_method(cBitmap, "sub"   , rbal_bitmap_sub, 4);
  rb_define_method(cBitmap, "clone" , rbal_bitmap_clone, 1);
  rb_define_method(cBitmap, "lock?" , rbal_bitmap_lock_p, 0);
  rb_define_method(cBitmap, "lock!"        , rbal_bitmap_lock, 2);
  rb_define_method(cBitmap, "lock_region!" , rbal_bitmap_lock, 6);
  rb_define_method(cBitmap, "unlock!"      , rbal_bitmap_unlock, 0);
  
  rb_define_singleton_method(cBitmap, "setblender", rbal_set_blender, 3);
  rb_define_singleton_method(cBitmap, "blender"   , rbal_get_blender, 0);
  
  rb_define_singleton_method(cBitmap, "setalphablender",
                             rbal_set_separate_blender, 6);
  rb_define_singleton_method(cBitmap, "alphablender"   ,
                             rbal_get_separate_blender, 0);
    
}




