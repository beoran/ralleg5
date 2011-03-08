#include "ralleg5.h"
#include "allegro5/allegro_primitives.h"

/* These are called "Primitives" in Allegro, but I think
"Draw" is a simpler name for this. */

static VALUE cDraw;
  
VALUE rbal_draw_init(VALUE rself) {
  return RBH_INT_BOOL(al_init_primitives_addon());
}
   
VALUE rbal_draw_done(VALUE rself) {
  al_shutdown_primitives_addon();
  return rself;
}



/*
* High level primitives. Others may be wrapped later.
*/

VALUE rbal_draw_line(VALUE rself, 
                     VALUE rx1, VALUE ry1, VALUE rx2, VALUE ry2,
                     VALUE rcolor, VALUE rthick) {
  float 
  x1 = RBH_FLOAT(rx1), 
  x2 = RBH_FLOAT(rx2),
  y1 = RBH_FLOAT(ry1), 
  y2 = RBH_FLOAT(ry2),
  th = RBH_FLOAT(rthick);
  ALLEGRO_COLOR color = rbal_color_struct(rcolor);
  al_draw_line(x1, y1, x2, y2, color, th); 
  return rself;
}


VALUE rbal_draw_triangle(VALUE rself, 
                     VALUE rx1, VALUE ry1, VALUE rx2, VALUE ry2,
                     VALUE rx3, VALUE ry3, VALUE rcolor, VALUE rthick) {
  float 
  x1 = RBH_FLOAT(rx1), 
  x2 = RBH_FLOAT(rx2),
  x3 = RBH_FLOAT(rx3),
  y1 = RBH_FLOAT(ry1), 
  y2 = RBH_FLOAT(ry2),
  y3 = RBH_FLOAT(ry3),
  th = RBH_FLOAT(rthick);
  ALLEGRO_COLOR color = rbal_color_struct(rcolor);
  al_draw_triangle(x1, y1, x2, y2, x3, y3, color, th); 
  return rself;
}

VALUE rbal_draw_rectangle(VALUE rself, 
                     VALUE rx1, VALUE ry1, VALUE rx2, VALUE ry2,
                     VALUE rcolor, VALUE rthick) {
  float 
  x1 = RBH_FLOAT(rx1), 
  x2 = RBH_FLOAT(rx2),
  y1 = RBH_FLOAT(ry1), 
  y2 = RBH_FLOAT(ry2),
  th = RBH_FLOAT(rthick);
  ALLEGRO_COLOR color = rbal_color_struct(rcolor);
  al_draw_rectangle(x1, y1, x2, y2, color, th); 
  return rself;
}

VALUE rbal_draw_roundrect(VALUE rself, 
                     VALUE rx1, VALUE ry1, VALUE rx2, VALUE ry2,
                     VALUE rrx, VALUE rry, VALUE rcolor, VALUE rthick) {
  float 
  x1 = RBH_FLOAT(rx1), 
  x2 = RBH_FLOAT(rx2),
  y1 = RBH_FLOAT(ry1), 
  y2 = RBH_FLOAT(ry2),
  ry = RBH_FLOAT(rry),
  rx = RBH_FLOAT(rrx),
  th = RBH_FLOAT(rthick);
  ALLEGRO_COLOR color = rbal_color_struct(rcolor);
  al_draw_rounded_rectangle(x1, y1, x2, y2, rx, ry, color, th); 
  return rself;
}

VALUE rbal_draw_circle(VALUE rself, 
                       VALUE rcx, VALUE rcy, VALUE rr, 
                       VALUE rcolor, VALUE rthick) {
  float 
  cx = RBH_FLOAT(rcx), 
  cy = RBH_FLOAT(rcy),
  r  = RBH_FLOAT(rr), 
  th = RBH_FLOAT(rthick);
  ALLEGRO_COLOR color = rbal_color_struct(rcolor);
  al_draw_circle(cx, cy, r, color, th); 
  return rself;
}

VALUE rbal_draw_ellipse(VALUE rself, 
                     VALUE rcx, VALUE rcy, VALUE rrx, VALUE rry,
                     VALUE rcolor, VALUE rthick) {
  float 
  cx = RBH_FLOAT(rcx), 
  cy = RBH_FLOAT(rcy),
  rx = RBH_FLOAT(rrx), 
  ry = RBH_FLOAT(rry),
  th = RBH_FLOAT(rthick);
  ALLEGRO_COLOR color = rbal_color_struct(rcolor);
  al_draw_ellipse(cx, cy, rx, ry, color, th); 
  return rself;
}


VALUE rbal_draw_arc(VALUE rself, 
                     VALUE rcx, VALUE rcy, VALUE rr, VALUE rstart, VALUE rdelta,
                     VALUE rcolor, VALUE rthick) {
  float 
  cx = RBH_FLOAT(rcx), 
  cy = RBH_FLOAT(rcy),
  r  = RBH_FLOAT(rr),
  st = RBH_FLOAT(rstart), 
  de = RBH_FLOAT(rdelta),
  th = RBH_FLOAT(rthick);
  ALLEGRO_COLOR color = rbal_color_struct(rcolor);
  al_draw_arc(cx, cy, r , st, de, color, th); 
  return rself;
}

VALUE rbal_draw_spline(VALUE rself, VALUE rpoints, VALUE rcolor, VALUE rthick) {
  float points[8]     = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
  float th            = RBH_FLOAT(rthick);
  ALLEGRO_COLOR color = rbal_color_struct(rcolor);
  int index           = 0;
  Check_Type(rpoints, T_ARRAY);
  if(RARRAY_SIZE(rpoints)<8) return 0;
  for (index=0; index < 8; index++) {
    points[index] = RBH_FLOAT(rb_ary_entry(rpoints, index));
  } 
  al_draw_spline(points, color, th); 
  return rself;
}


VALUE rbal_fill_triangle(VALUE rself, 
                     VALUE rx1, VALUE ry1, VALUE rx2, VALUE ry2,
                     VALUE rx3, VALUE ry3, VALUE rcolor) {
  float 
  x1 = RBH_FLOAT(rx1), 
  x2 = RBH_FLOAT(rx2),
  x3 = RBH_FLOAT(rx3),
  y1 = RBH_FLOAT(ry1), 
  y2 = RBH_FLOAT(ry2),
  y3 = RBH_FLOAT(ry3);
  ALLEGRO_COLOR color = rbal_color_struct(rcolor);
  al_draw_filled_triangle(x1, y1, x2, y2, x3, y3, color); 
  return rself;
}

VALUE rbal_fill_rectangle(VALUE rself, 
                     VALUE rx1, VALUE ry1, VALUE rx2, VALUE ry2,
                     VALUE rcolor) {
  float 
  x1 = RBH_FLOAT(rx1), 
  x2 = RBH_FLOAT(rx2),
  y1 = RBH_FLOAT(ry1), 
  y2 = RBH_FLOAT(ry2);
  ALLEGRO_COLOR color = rbal_color_struct(rcolor);
  al_draw_filled_rectangle(x1, y1, x2, y2, color); 
  return rself;
}

VALUE rbal_fill_roundrect(VALUE rself, 
                     VALUE rx1, VALUE ry1, VALUE rx2, VALUE ry2,
                     VALUE rrx, VALUE rry, VALUE rcolor) {
  float 
  x1 = RBH_FLOAT(rx1), 
  x2 = RBH_FLOAT(rx2),
  y1 = RBH_FLOAT(ry1), 
  y2 = RBH_FLOAT(ry2),
  ry = RBH_FLOAT(rry),
  rx = RBH_FLOAT(rrx);
  ALLEGRO_COLOR color = rbal_color_struct(rcolor);
  al_draw_filled_rounded_rectangle(x1, y1, x2, y2, rx, ry, color); 
  return rself;
}

VALUE rbal_fill_circle(VALUE rself, 
                       VALUE rcx, VALUE rcy, VALUE rr, 
                       VALUE rcolor) {
  float 
  cx = RBH_FLOAT(rcx), 
  cy = RBH_FLOAT(rcy),
  r  = RBH_FLOAT(rr);
  ALLEGRO_COLOR color = rbal_color_struct(rcolor);
  al_draw_filled_circle(cx, cy, r, color); 
  return rself;
}

VALUE rbal_fill_ellipse(VALUE rself, 
                     VALUE rcx, VALUE rcy, VALUE rrx, VALUE rry,
                     VALUE rcolor) {
  float 
  cx = RBH_FLOAT(rcx), 
  cy = RBH_FLOAT(rcy),
  rx = RBH_FLOAT(rrx), 
  ry = RBH_FLOAT(rry);
  ALLEGRO_COLOR color = rbal_color_struct(rcolor);
  al_draw_filled_ellipse(cx, cy, rx, ry, color); 
  return rself;
}



/*

ALLEGRO_PRIM_FUNC(void, al_draw_filled_triangle, (float x1, float y1, float x2, float y2, float x3, float y3, ALLEGRO_COLOR color));
ALLEGRO_PRIM_FUNC(void, al_draw_filled_rectangle, (float x1, float y1, float x2, float y2, ALLEGRO_COLOR color));
ALLEGRO_PRIM_FUNC(void, al_draw_filled_ellipse, (float cx, float cy, float rx, float ry, ALLEGRO_COLOR color));
ALLEGRO_PRIM_FUNC(void, al_draw_filled_circle, (float cx, float cy, float r, ALLEGRO_COLOR color));
ALLEGRO_PRIM_FUNC(void, al_draw_filled_rounded_rectangle, (float x1, float y1, float x2, float y2, float rx, float ry, ALLEGRO_COLOR color));
*/

void ralleg5_draw_init(VALUE mAl) {
  cDraw = rb_define_module_under(mAl, "Draw");
  rb_define_singleton_method(cDraw, "init"           , rbal_draw_init     , 0); 
  rb_define_singleton_method(cDraw, "done"           , rbal_draw_done     , 0);
  rb_define_singleton_method(cDraw, "draw_triangle"  , rbal_draw_triangle , 8);
  rb_define_singleton_method(cDraw, "fill_triangle"  , rbal_fill_triangle , 7);
  rb_define_singleton_method(cDraw, "draw_rectangle" , rbal_draw_rectangle, 6);
  rb_define_singleton_method(cDraw, "fill_rectangle" , rbal_fill_rectangle, 5);  
  rb_define_singleton_method(cDraw, "draw_circle"    , rbal_draw_circle   , 5);
  rb_define_singleton_method(cDraw, "fill_circle"    , rbal_fill_circle   , 4);
  rb_define_singleton_method(cDraw, "draw_ellipse"   , rbal_draw_circle   , 6);
  rb_define_singleton_method(cDraw, "fill_ellipse"   , rbal_fill_ellipse  , 5);
  rb_define_singleton_method(cDraw, "draw_roundrect" , rbal_draw_roundrect, 8);
  rb_define_singleton_method(cDraw, "fill_roundrect" , rbal_fill_roundrect, 7);
  rb_define_singleton_method(cDraw, "draw_line"      , rbal_draw_line     , 5);
  rb_define_singleton_method(cDraw, "draw_spline"    , rbal_draw_spline   , 3);  
}
