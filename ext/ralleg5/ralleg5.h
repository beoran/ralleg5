#ifndef RALLEG5_INCLUDED
#define RALLEG5_INCLUDED

#include "allegro5/allegro.h"
#include "rubyhelp.h"

extern void ralleg5_display_init(VALUE mAl);
extern void ralleg5_mode_init(VALUE mAl);
extern void ralleg5_monitor_init(VALUE mAl);
extern void ralleg5_color_init(VALUE mAl);
extern void ralleg5_bitmap_init(VALUE mAl);


/* Converts a ruby string to utf-8 */
extern VALUE rb_str_to_utf8(VALUE text);
 
/* Unwraps a Color value to a struct. 
Will return an all zero struct if it had any problems unwrapping the struct. 
*/
ALLEGRO_COLOR rbal_color_struct(VALUE rself);

/* Wraps a color struct by ways of allocating a pointer. */
VALUE rbal_color_wrapstruct(ALLEGRO_COLOR col);




#endif
