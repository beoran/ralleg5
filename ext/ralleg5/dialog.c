#include "ralleg5.h"
#include "allegro5/allegro_native_dialog.h"

#ifdef RALLEG5_WITH_DIALOG

/** Unbfortunately, native dialogs won't work on some older versions of GDK.
* Therefore, I have to postpose wrapping them for now, 
* and make it optional later.  
*/

VALUE cDialog;
VALUE cTextlog;
VALUE cFilechooser;

VALUE rbal_filechooser_wrap(ALLEGRO_FILECHOOSER * ptr, int gc) {
  if(!ptr) return Qnil;
  if (gc == RBAL_GC) {
    return Data_Wrap_Struct(cFilechooser, 0, al_destroy_native_file_dialog, ptr);
  } else {
    return Data_Wrap_Struct(cFilechooser, 0, 0, ptr);
  } 
}


/* Unwraps filechooser from a Ruby object */
ALLEGRO_FILECHOOSER * rbal_filechooser_unwrap(VALUE rself) { 
  ALLEGRO_FILECHOOSER * result;
  if (rself == Qnil) return NULL;
  Data_Get_Struct(rself, ALLEGRO_FILECHOOSER, result);
  return result;
}

/*

ALLEGRO_DIALOG_FUNC(ALLEGRO_FILECHOOSER *, al_create_native_file_dialog, (char const *initial_path,
   char const *title, char const *patterns, int mode));
ALLEGRO_DIALOG_FUNC(bool, al_show_native_file_dialog, (ALLEGRO_DISPLAY *display, ALLEGRO_FILECHOOSER *dialog));
ALLEGRO_DIALOG_FUNC(int, al_get_native_file_dialog_count, (const ALLEGRO_FILECHOOSER *dialog));
ALLEGRO_DIALOG_FUNC(const char *, al_get_native_file_dialog_path, (const ALLEGRO_FILECHOOSER *dialog,
   size_t index));
ALLEGRO_DIALOG_FUNC(void, al_destroy_native_file_dialog, (ALLEGRO_FILECHOOSER *dialog));

ALLEGRO_DIALOG_FUNC(int, al_show_native_message_box, (ALLEGRO_DISPLAY *display, char const *title,
   char const *heading, char const *text, char const *buttons, int flags));

ALLEGRO_DIALOG_FUNC(ALLEGRO_TEXTLOG *, al_open_native_text_log, (char const *title, int flags));
ALLEGRO_DIALOG_FUNC(void, al_close_native_text_log, (ALLEGRO_TEXTLOG *textlog));
ALLEGRO_DIALOG_FUNC(void, al_append_native_text_log, (ALLEGRO_TEXTLOG *textlog, char const *format, ...));
ALLEGRO_DIALOG_FUNC(ALLEGRO_EVENT_SOURCE *, al_get_native_text_log_event_source, (ALLEGRO_TEXTLOG *textlog));

ALLEGRO_DIALOG_FUNC(uint32_t, al_get_allegro_native_dialog_version, (void));


enum {
   ALLEGRO_FILECHOOSER_FILE_MUST_EXIST = 1,
   ALLEGRO_FILECHOOSER_SAVE            = 2,
   ALLEGRO_FILECHOOSER_FOLDER          = 4,
   ALLEGRO_FILECHOOSER_PICTURES        = 8,
   ALLEGRO_FILECHOOSER_SHOW_HIDDEN     = 16,
   ALLEGRO_FILECHOOSER_MULTIPLE        = 32
};

enum {
   ALLEGRO_MESSAGEBOX_WARN             = 1<<0,
   ALLEGRO_MESSAGEBOX_ERROR            = 1<<1,
   ALLEGRO_MESSAGEBOX_OK_CANCEL        = 1<<2,
   ALLEGRO_MESSAGEBOX_YES_NO           = 1<<3,
   ALLEGRO_MESSAGEBOX_QUESTION         = 1<<4
};

enum {
   ALLEGRO_TEXTLOG_NO_CLOSE            = 1<<0,
   ALLEGRO_TEXTLOG_MONOSPACE           = 1<<1
};

enum {
   ALLEGRO_EVENT_NATIVE_DIALOG_CLOSE   = 600
};
*/

#endif

