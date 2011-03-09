#include "ralleg5.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"



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

// Wraps a into a Ruby object, optionally garbage collected. 
VALUE rbal__wrap(ALLEGRO_ * ptr, int gc) {
  if(!ptr) return Qnil;
  if (gc == RBAL_GC) {
    return Data_Wrap_Struct(c, 0, , ptr);
  } else {
    return Data_Wrap_Struct(c, 0, 0, ptr);
  } 
}

// Unwraps a from a Ruby object 
ALLEGRO_   * rbal__unwrap(VALUE rself) { 
  ALLEGRO_ * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_, result);
  return result;
}





*/

VALUE cFont;

// Wraps a into a Ruby object, optionally garbage collected. 
VALUE rbal_font_wrap(ALLEGRO_FONT * ptr, int gc) {
  if(!ptr) return Qnil;
  if (gc == RBAL_GC) {
    return Data_Wrap_Struct(cFont, 0, al_destroy_font, ptr);
  } else {
    return Data_Wrap_Struct(cFont, 0, 0, ptr);
  } 
}

// Unwraps a from a Ruby object 
ALLEGRO_FONT  * rbal_font_unwrap(VALUE rself) { 
  ALLEGRO_FONT * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_FONT, result);
  return result;
}


/* will not be wrapped: 
al_register_font_loader
*/

VALUE rbal_load_bitmap_font(VALUE r_, VALUE rfilename) { 
  const char *filename       = RBH_CSTR(rfilename);
  return rbal_font_wrap(al_load_bitmap_font(filename), RBAL_NO_GC);
} 

VALUE rbal_font_load_bitmap(VALUE r_, VALUE rfilename) { 
  const char *filename       = RBH_CSTR(rfilename);
  return rbal_font_wrap(al_load_bitmap_font(filename), RBAL_GC);
} 

VALUE rbal_load_font(VALUE r_, VALUE rfilename, VALUE rsize, VALUE rflags) { 
  const char *filename       = RBH_CSTR(rfilename);
  ALLEGRO_FONT * font = al_load_font(filename, RBH_INT(rsize), RBH_UINT(rflags));
  return rbal_font_wrap(font, RBAL_NO_GC);
} 

VALUE rbal_font_load(VALUE r_, VALUE rfilename, VALUE rsize, VALUE rflags) { 
  const char *filename       = RBH_CSTR(rfilename);
  ALLEGRO_FONT * font = al_load_font(filename, RBH_INT(rsize), RBH_UINT(rflags));
  return rbal_font_wrap(font, RBAL_GC);
} 

/* TODO: 
ALLEGRO_FONT_FUNC(ALLEGRO_FONT *, al_grab_font_from_bitmap, (ALLEGRO_BITMAP *bmp, int n, int ranges[]));
*/

VALUE rbal_font_draw_ustr(VALUE r_, VALUE rfont, VALUE rcolor, 
                          VALUE rx, VALUE ry, VALUE rflags, VALUE rustr) {
  ALLEGRO_FONT * font   = rbal_font_unwrap(rfont);
  ALLEGRO_COLOR  color  = rbal_color_struct(rcolor);
  float          x      = RBH_FLOAT(rx), 
                 y      = RBH_FLOAT(ry);
  ALLEGRO_USTR * ustr   = rbal_ustr_unwrap(rustr);                 
  al_draw_ustr(font, color, x, y, RBH_INT(rflags), ustr);
  return r_;
}

VALUE rbal_font_draw_text(VALUE r_, VALUE rfont, VALUE rcolor, 
                          VALUE rx, VALUE ry, VALUE rflags, VALUE rtext) {
  ALLEGRO_FONT * font   = rbal_font_unwrap(rfont);
  ALLEGRO_COLOR  color  = rbal_color_struct(rcolor);
  float          x      = RBH_FLOAT(rx), 
                 y      = RBH_FLOAT(ry);
  char *         text   = RBH_CSTR(rtext);
  al_draw_text(font, color, x, y, RBH_INT(rflags), text);
  return r_;
}

VALUE rbal_font_draw_justified_ustr(VALUE r_, VALUE rfont, VALUE rcolor, 
                                    VALUE rx1, VALUE rx2, VALUE ry, VALUE rdiff,
                                    VALUE rflags, VALUE rustr) {
  ALLEGRO_FONT * font   = rbal_font_unwrap(rfont);
  ALLEGRO_COLOR  color  = rbal_color_struct(rcolor);
  float          x1     = RBH_FLOAT(rx1),
                 x2     = RBH_FLOAT(rx2), 
                 y      = RBH_FLOAT(ry),
                 diff   = RBH_FLOAT(rdiff);
  ALLEGRO_USTR * ustr   = rbal_ustr_unwrap(rustr);                 
  al_draw_justified_ustr(font, color, x1, x2, y, diff, RBH_INT(rflags), ustr);
  return r_;
}

VALUE rbal_font_draw_justified_text(VALUE r_, VALUE rfont, VALUE rcolor, 
                                    VALUE rx1, VALUE rx2, VALUE ry, VALUE rdiff, 
                                    VALUE rflags, VALUE rtext) {
  ALLEGRO_FONT * font   = rbal_font_unwrap(rfont);
  ALLEGRO_COLOR  color  = rbal_color_struct(rcolor);
  float          x1     = RBH_FLOAT(rx1),
                 x2     = RBH_FLOAT(rx2), 
                 y      = RBH_FLOAT(ry),
                 diff   = RBH_FLOAT(rdiff);
  char *         text   = RBH_CSTR(rtext);
  al_draw_justified_text(font, color, x1, x2, y, diff, RBH_INT(rflags), text);
  return r_;
}

/* Not supported, since ruby can format strings by itself:
al_draw_textf,
al_draw_justified_textf
*/

VALUE rbal_get_text_width(VALUE r_, VALUE rfont, VALUE rtext) {
  ALLEGRO_FONT * font   = rbal_font_unwrap(rfont);
  char *         text   = RBH_CSTR(rtext);
  return RBH_INT_NUM(al_get_text_width(font, text));  
}

VALUE rbal_get_ustr_width(VALUE r_, VALUE rfont, VALUE rustr) {
  ALLEGRO_FONT * font   = rbal_font_unwrap(rfont);  
  ALLEGRO_USTR * ustr   = rbal_ustr_unwrap(rustr);  
  return RBH_INT_NUM(al_get_ustr_width(font, ustr));  
}

VALUE rbal_get_font_line_height(VALUE r_, VALUE rfont) {
  ALLEGRO_FONT * font   = rbal_font_unwrap(rfont); 
  return RBH_INT_NUM(al_get_font_line_height(font));  
}

VALUE rbal_get_font_ascent(VALUE r_, VALUE rfont) {
  ALLEGRO_FONT * font   = rbal_font_unwrap(rfont);
  return RBH_INT_NUM(al_get_font_ascent(font));  
}

VALUE rbal_get_font_descent(VALUE r_, VALUE rfont) {
  ALLEGRO_FONT * font   = rbal_font_unwrap(rfont);
  return RBH_INT_NUM(al_get_font_descent(font));  
}

VALUE rbal_destroy_font(VALUE r_, VALUE rfont) {
  ALLEGRO_FONT * font   = rbal_font_unwrap(rfont);
  al_destroy_font(font);
  return r_;
}


VALUE rbal_get_text_dimensions(VALUE r_, VALUE rfont, VALUE rtext) {
  ALLEGRO_FONT * font   = rbal_font_unwrap(rfont);
  char *         text   = RBH_CSTR(rtext);
  int bbx = 0, bby = 0, bbw = 0 , bbh = 0;
  al_get_text_dimensions(font, text, &bbx, &bby, &bbw, &bbh);  
  return rb_ary_new3(4, 
    RBH_INT_NUM(bbx), RBH_INT_NUM(bby), RBH_INT_NUM(bbw), RBH_INT_NUM(bbh));  
}

VALUE rbal_get_ustr_dimensions(VALUE r_, VALUE rfont, VALUE rustr) {
  ALLEGRO_FONT * font   = rbal_font_unwrap(rfont);  
  ALLEGRO_USTR * ustr   = rbal_ustr_unwrap(rustr);
  int bbx = 0, bby = 0, bbw = 0 , bbh = 0;
  al_get_ustr_dimensions(font, ustr, &bbx, &bby, &bbw, &bbh);  
  return rb_ary_new3(4, 
    RBH_INT_NUM(bbx), RBH_INT_NUM(bby), RBH_INT_NUM(bbw), RBH_INT_NUM(bbh));  
  return RBH_INT_NUM(al_get_ustr_width(font, ustr));  
}


VALUE rbal_init_font_addon(VALUE r_) {
  al_init_font_addon();
  return r_;
}
   
VALUE rbal_shutdown_font_addon(VALUE r_) {
  al_shutdown_font_addon();
  return r_;
}
   
VALUE rbal_get_allegro_font_version(VALUE rself) {
  return RBH_UINT_NUM(al_get_allegro_font_version());
}

VALUE rbal_load_ttf_font(VALUE r_, VALUE rfilename, VALUE rsize, VALUE rflags) { 
  const char *filename       = RBH_CSTR(rfilename);
  ALLEGRO_FONT * font        = al_load_ttf_font(filename, RBH_INT(rsize),
                                                RBH_UINT(rflags));
  return rbal_font_wrap(font, RBAL_NO_GC);
} 

VALUE rbal_font_load_ttf(VALUE r_, VALUE rfilename, VALUE rsize, VALUE rflags) { 
  const char *filename       = RBH_CSTR(rfilename);
  ALLEGRO_FONT * font = al_load_ttf_font(filename, RBH_INT(rsize),
                                         RBH_UINT(rflags));
  return rbal_font_wrap(font, RBAL_GC);
} 


/* TODO: 
ALLEGRO_TTF_FUNC(ALLEGRO_FONT *, al_load_ttf_font_f, (ALLEGRO_FILE *file, char const *filename, int size, int flags));
*/

VALUE rbal_init_ttf_addon(VALUE r_) {
  al_init_ttf_addon();
  return r_;
}
   
VALUE rbal_shutdown_ttf_addon(VALUE r_) {
  al_shutdown_ttf_addon();
  return r_;
}
   
VALUE rbal_get_allegro_ttf_version(VALUE rself) {
  return RBH_UINT_NUM(al_get_allegro_ttf_version());
}


void ralleg5_font_init(VALUE mAl, VALUE mLow) {
  cFont = rb_define_class_under(mAl, "Font"   , rb_cObject);
  rb_define_singleton_method(cFont, "load_bitmap", rbal_font_load_bitmap, 1);
  rb_define_singleton_method(cFont, "load_ttf"   , rbal_font_load_ttf, 3);
  rb_define_singleton_method(cFont, "load"       , rbal_font_load, 3);
  
  rbal_low_const(mLow , ALLEGRO_ALIGN_LEFT          );
  rbal_low_const(mLow , ALLEGRO_ALIGN_CENTRE        );
  rbal_low_const(mLow , ALLEGRO_ALIGN_RIGHT         );
  rbal_low_func(mLow  , al_load_bitmap_font             , 1 );
  rbal_low_func(mLow  , al_load_font                    , 3 );
  rbal_low_func(mLow  , al_load_ttf_font                , 3 );
  rbal_low_func(mLow  , al_font_draw_ustr               , 6 );
  rbal_low_func(mLow  , al_font_draw_text               , 6 );
  rbal_low_func(mLow  , al_font_draw_justified_ustr     , 7 );
  rbal_low_func(mLow  , al_font_draw_justified_text     , 7 );
  
  rbal_low_func(mLow  , al_get_text_width               , 2 );
  rbal_low_func(mLow  , al_get_ustr_width               , 2 );
  rbal_low_func(mLow  , al_get_font_line_height         , 1 );
  rbal_low_func(mLow  , al_get_font_ascent              , 1 );
  rbal_low_func(mLow  , al_get_font_descent             , 1 );
  rbal_low_func(mLow  , al_destroy_font                 , 1 );
  rbal_low_func(mLow  , al_get_text_dimensions          , 2 );
  rbal_low_func(mLow  , al_get_ustr_dimensions          , 2 );
  rbal_low_func(mLow  , al_init_font_addon              , 0 );
  rbal_low_func(mLow  , al_shutdown_font_addon          , 0 );
  rbal_low_func(mLow  , al_get_allegro_font_version     , 0 );
  
  rbal_low_func(mLow  , al_init_ttf_addon               , 0 );
  rbal_low_func(mLow  , al_shutdown_ttf_addon           , 0 );  
  rbal_low_func(mLow  , al_get_allegro_ttf_version      , 0 );
  
}
