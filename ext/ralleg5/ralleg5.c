
#include "ralleg5.h"

/* Allegro namespace module. */
static VALUE mAl;

/* Low level wrapper module. */
static VALUE mLow;

/*Utility functions */

/* Converts a ruby string to utf-8 */
VALUE rb_str_to_utf8(VALUE text) { 
  return rb_str_export_to_enc(text, rb_utf8_encoding());
}



/** Suystem functions from system.h */


/**
* @overload version
* Returns the (compiled) version of the Allegro library, packed into a single 
* integer as groups of 8 * bits in the form 
* (major << 24) | (minor << 16) | (revision << 8) | release.
*/
VALUE rbal_get_allegro_version(VALUE vself) {
  return RBH_INT_NUM(al_get_allegro_version());
} 

VALUE rbal_init(VALUE rself) {
  return RBH_INT_BOOL(al_init());
}

VALUE rbal_install_system(VALUE rself) {
  return RBH_INT_BOOL(al_install_system(ALLEGRO_VERSION_INT, atexit));
} 

VALUE rbal_uninstall_system(VALUE rself) {
  al_uninstall_system();
  return Qnil;
} 

VALUE rbal_is_system_installed(VALUE rself) {
  return RBH_INT_BOOL(al_is_system_installed());
}

VALUE rbal_inhibit_screensaver(VALUE rself, VALUE rinhibit) {
  return RBH_INT_BOOL(al_inhibit_screensaver(RBH_BOOL_INT(rinhibit)));
} 



/*
AL_FUNC(bool, al_install_system, (int version, int (*atexit_ptr)(void (*)(void))));
AL_FUNC(void, al_uninstall_system, (void));
AL_FUNC(bool, al_is_system_installed, (void));
AL_FUNC(ALLEGRO_SYSTEM *, al_get_system_driver, (void));
AL_FUNC(ALLEGRO_CONFIG *, al_get_system_config, (void));


AL_FUNC(ALLEGRO_PATH *, al_get_standard_path, (int id));

AL_FUNC(void, al_set_org_name, (const char *org_name));
AL_FUNC(void, al_set_app_name, (const char *app_name));
AL_FUNC(const char *, al_get_org_name, (void));
AL_FUNC(const char *, al_get_app_name, (void));

AL_FUNC(bool, al_inhibit_screensaver, (bool inhibit));
*/

void ralleg5_system_init(VALUE mAl, VALUE mLow) {
  rb_define_singleton_method(mAl, "version"   , rbal_get_allegro_version  , 0);
  rb_define_singleton_method(mAl, "init"      , rbal_init		  , 0);
  rb_define_singleton_method(mAl, "install"   , rbal_install_system       , 0);
  rb_define_singleton_method(mAl, "uninstall" , rbal_uninstall_system     , 0);
  rb_define_singleton_method(mAl, "install?"  , rbal_is_system_installed  , 0);
  rb_define_singleton_method(mAl, "no_screensaver", rbal_inhibit_screensaver, 1);


  
  rb_define_const(mAl, "RESOURCES_PATH"     , UINT2NUM(ALLEGRO_RESOURCES_PATH));
  rb_define_const(mAl, "TEMP_PATH"          , UINT2NUM(ALLEGRO_TEMP_PATH));
  rb_define_const(mAl, "USER_DATA_PATH"     , UINT2NUM(ALLEGRO_USER_DATA_PATH));
  rb_define_const(mAl, "USER_HOME_PATH"	    , UINT2NUM(ALLEGRO_USER_HOME_PATH));
  rb_define_const(mAl, "USER_SETTINGS_PATH" , UINT2NUM(ALLEGRO_USER_SETTINGS_PATH));
  rb_define_const(mAl, "USER_DOCUMENTS_PATH", UINT2NUM(ALLEGRO_USER_DOCUMENTS_PATH));
  rb_define_const(mAl, "EXENAME_PATH"       , UINT2NUM(ALLEGRO_EXENAME_PATH));
  
  /* Low level interface below: */
  rbal_low_func(mLow, al_get_allegro_version, 0);
  rbal_low_func(mLow, al_init               , 0);
  rbal_low_func(mLow, al_install_system     , 0);
  rbal_low_func(mLow, al_uninstall_system   , 0);
  rbal_low_func(mLow, al_is_system_installed, 0);
  rbal_low_func(mLow, al_inhibit_screensaver, 0);
  rbal_low_const(mLow, ALLEGRO_RESOURCES_PATH);
  rbal_low_const(mLow, ALLEGRO_TEMP_PATH);
  rbal_low_const(mLow, ALLEGRO_USER_DATA_PATH);
  rbal_low_const(mLow, ALLEGRO_USER_HOME_PATH);
  rbal_low_const(mLow, ALLEGRO_USER_SETTINGS_PATH);
  rbal_low_const(mLow, ALLEGRO_USER_DOCUMENTS_PATH);
  rbal_low_const(mLow, ALLEGRO_EXENAME_PATH);  
}


/** Entry point for Ruby. */
void Init_ralleg5() {
  mAl   = rb_define_module("Al"); 
  mLow  = rb_define_module_under(mAl, "Low");
  ralleg5_system_init(mAl, mLow); 
  ralleg5_mode_init(mAl);  
  ralleg5_monitor_init(mAl);
  ralleg5_color_init(mAl);
  ralleg5_bitmap_init(mAl);
  ralleg5_event_init(mAl); 
  ralleg5_display_init(mAl);
  ralleg5_joystick_init(mAl);
  ralleg5_keyboard_init(mAl);
  ralleg5_draw_init(mAl);
  ralleg5_audio_init(mAl, mLow);
  ralleg5_ustr_init(mAl, mLow);
  
}







