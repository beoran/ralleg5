#include "ralleg5.h"
#include "allegro5/allegro_primitives.h"

/* These are called "Primitives" in Allegro, but I think
"Draw" is a simpler name for this. */

/* A vertex class for al_draw_prim. */

static VALUE cVertex; 

ALLEGRO_VERTEX * rbal_vertex_alloc() {
  return al_calloc(sizeof(ALLEGRO_VERTEX), 1);
}

void rbal_vertex_free(ALLEGRO_VERTEX * ptr) {
  al_free(ptr);
}

ALLEGRO_VERTEX * rbal_vertex_init(ALLEGRO_VERTEX * ptr,
  float x, float y, float z, float u, float v, ALLEGRO_COLOR color) {
  if (!ptr) return NULL;
  ptr->x = x; 
  ptr->y = y;
  ptr->z = z;
  ptr->u = u;
  ptr->v = v;
  ptr->color = color;
}

ALLEGRO_VERTEX * rbal_vertex_make(float x, float y, float z, float u, float v, ALLEGRO_COLOR color) {
  ALLEGRO_VERTEX * vert = rbal_vertex_alloc();
  return rbal_vertex_init(vert, x, y, z, u, v, color);
}





/* Wraps a vertex into a Ruby object, optionally garbage collected. */
VALUE rbal_vertex_wrap(ALLEGRO_VERTEX * ptr, int gc) {
  if(!ptr) return Qnil;
  if (gc) {
    return Data_Wrap_Struct(cVertex, 0, rbal_vertex_free, ptr);
  } else {
    return Data_Wrap_Struct(cVertex, 0, 0, ptr);
  } 
}

/* Unwraps a vertex from a ruby object */
ALLEGRO_VERTEX * rbal_vertex_unwrap(VALUE rself) { 
  ALLEGRO_VERTEX * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_VERTEX, result);
  return result;
}

VALUE rbal_create_vertex(VALUE r_, VALUE rx, VALUE ry, 
                         VALUE rz, VALUE ru, VALUE rv, VALUE rcolor) {
  ALLEGRO_COLOR color   = rbal_color_struct(rcolor);
  float x               = RBH_FLOAT(rx);
  float y               = RBH_FLOAT(ry);
  float z               = RBH_FLOAT(rz);
  float u               = RBH_FLOAT(ru);
  float v               = RBH_FLOAT(rv);
  ALLEGRO_VERTEX * vert = rbal_vertex_make(x, y, z, u, v , color);
  return rbal_vertex_wrap(vert, RBAL_NO_GC);  
}

VALUE rbal_vertex_create(VALUE r_, VALUE rx, VALUE ry, 
                         VALUE rz, VALUE ru, VALUE rv, VALUE rcolor) {
  ALLEGRO_COLOR color   = rbal_color_struct(rcolor);
  float x               = RBH_FLOAT(rx);
  float y               = RBH_FLOAT(ry);
  float z               = RBH_FLOAT(rz);
  float u               = RBH_FLOAT(ru);
  float v               = RBH_FLOAT(rv);
  ALLEGRO_VERTEX * vert = rbal_vertex_make(x, y, z, u, v , color);
  return rbal_vertex_wrap(vert, RBAL_GC);  
}

VALUE rbal_destroy_vertex(VALUE r_, VALUE rvert ) {
  ALLEGRO_VERTEX * vert = rbal_vertex_unwrap(rvert);
  rbal_vertex_free(vert);
  return r_;  
}

VALUE rbal_vertex_x(VALUE r_, VALUE rvert ) {
  ALLEGRO_VERTEX * vert = rbal_vertex_unwrap(rvert);
  if(!vert) return Qnil;
  return RBH_FLOAT_NUM(vert->x);  
}

VALUE rbal_vertex_y(VALUE r_, VALUE rvert ) {
  ALLEGRO_VERTEX * vert = rbal_vertex_unwrap(rvert);
  if(!vert) return Qnil;
  return RBH_FLOAT_NUM(vert->y);  
}

VALUE rbal_vertex_z(VALUE r_, VALUE rvert ) {
  ALLEGRO_VERTEX * vert = rbal_vertex_unwrap(rvert);
  if(!vert) return Qnil;
  return RBH_FLOAT_NUM(vert->z);  
}

VALUE rbal_vertex_u(VALUE r_, VALUE rvert ) {
  ALLEGRO_VERTEX * vert = rbal_vertex_unwrap(rvert);
  if(!vert) return Qnil;
  return RBH_FLOAT_NUM(vert->x);  
}

VALUE rbal_vertex_v(VALUE r_, VALUE rvert ) {
  ALLEGRO_VERTEX * vert = rbal_vertex_unwrap(rvert);
  if(!vert) return Qnil;
  return RBH_FLOAT_NUM(vert->x);  
}

VALUE rbal_vertex_color(VALUE r_, VALUE rvert ) {
  ALLEGRO_VERTEX * vert = rbal_vertex_unwrap(rvert);
  if (!vert) return Qnil;
  return rbal_color_wrap_struct(vert->color);  
}




/* Only ALLEGRO_VERTEX are supported, so the signature changes from C.
* verts must be a ruby array of ALLEGRO_VERTEX objects. 
*/
VALUE rbal_draw_prim(VALUE r_, VALUE rverts, VALUE rtexture, VALUE rtype) {
  ALLEGRO_BITMAP *  texture = rbal_bitmap_unwrap(rtexture);
  ALLEGRO_VERTEX *  verts   = NULL;
  int size                  = RARRAY_LEN(rtexture);
  int index                 = 0;
  int type                  = RBH_INT(rtype); 
  if(size < 0)              return Qnil;
  verts                     = al_calloc(sizeof(ALLEGRO_VERTEX), size);
  /* Copy vertices from ruby array to C array. */
  for(index = 0; index < size; index ++) {
    ALLEGRO_VERTEX * vert   = rbal_vertex_unwrap(rb_ary_entry(rverts, index));
    /* If one vertex is nil, just give up and draw nothing. */
    if (!vert) goto give_up; 
    verts[index]            = (*vert);
    /* Ouch, all this copying could be slow... */
  }
  al_draw_prim(verts, NULL, texture, 0, size, type);
  
  give_up: 
  /* Free up memory again. */
  al_free(verts);
  return r_;
}
 
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



void ralleg_vertext_init(VALUE mAl, VALUE mLow) {
  cVertex = rb_define_module_under(mAl, "Vertex");
  rb_define_singleton_method(cVertex, "create", rbal_vertex_create  , 6);
  
  rb_define_method(cVertex, "x"     , rbal_vertex_x     , 0);
  rb_define_method(cVertex, "y"     , rbal_vertex_y     , 0);
  rb_define_method(cVertex, "z"     , rbal_vertex_z     , 0);
  rb_define_method(cVertex, "u"     , rbal_vertex_u     , 0);
  rb_define_method(cVertex, "v"     , rbal_vertex_v     , 0);
  rb_define_method(cVertex, "color" , rbal_vertex_color , 0);
  
  rb_define_singleton_method(mLow, "al_create_vertex" , rbal_create_vertex, 6);
  rb_define_singleton_method(mLow, "al_destroy_vertex", rbal_destroy_vertex, 1);
  
  rbal_low_method(mLow, al_draw_prim                 , 3);
  
  rbal_low_const(mLow, ALLEGRO_PRIM_LINE_LIST);
  rbal_low_const(mLow, ALLEGRO_PRIM_LINE_STRIP);
  rbal_low_const(mLow, ALLEGRO_PRIM_LINE_LOOP);
  rbal_low_const(mLow, ALLEGRO_PRIM_TRIANGLE_LIST);
  rbal_low_const(mLow, ALLEGRO_PRIM_TRIANGLE_STRIP);
  rbal_low_const(mLow, ALLEGRO_PRIM_TRIANGLE_FAN);
  rbal_low_const(mLow, ALLEGRO_PRIM_POINT_LIST);
  rbal_low_const(mLow, ALLEGRO_PRIM_NUM_TYPES);

}


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

