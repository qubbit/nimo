#include <CoreFoundation/CoreFoundation.h>
#include <objc/objc-runtime.h>
#include <objc/objc.h>
#include <ruby.h>

// Guide: https://github.com/ruby/ruby/blob/trunk/doc/extension.rdoc
// void rb_define_singleton_method(VALUE object, const char *name,
//                                 VALUE (*func)(ANYARGS), int argc)

VALUE display_alert_panel(VALUE self, VALUE title, VALUE message) {
  Check_Type(title, T_STRING);
  Check_Type(message, T_STRING);

  char* title_ptr = RSTRING_PTR(title);
  char* message_ptr = RSTRING_PTR(message);

  printf("title: %s, message: %s\n", title_ptr, message_ptr);

  id app = NULL;
  id pool = (id)objc_getClass("NSAutoreleasePool");
  if (!pool) {
    printf("Unable to create NSAutoreleasePool...\nAborting...\n");
    return -1;
  }
  pool = objc_msgSend(pool, sel_registerName("alloc"));
  if (!pool) {
    printf("Unable to create NSAutoreleasePool...\nAborting...\n");
    return -1;
  }
  pool = objc_msgSend(pool, sel_registerName("init"));

  app = objc_msgSend((id)objc_getClass("NSApplication"),
                     sel_registerName("sharedApplication"));

  NSRunAlertPanel(CFStringCreateWithCString(NULL, title_ptr, kCFStringEncodingUTF8), CFStringCreateWithCString(NULL, message_ptr, kCFStringEncodingUTF8), CFSTR("OK"), NULL, NULL);
  objc_msgSend(pool, sel_registerName("release"));
}

VALUE nimo_hello() {
  printf("Hello, World!\n");
  // setDesktopImageURL("/Users/gadhikari/Wallpapers/eXpresso.jpg", 1, NULL);
  return Qnil;
}

void Init_nimo(void) {
  VALUE cNimo = rb_define_class("Nimo", rb_cObject);

  rb_define_singleton_method(cNimo, "hello", nimo_hello, 0);
  rb_define_singleton_method(cNimo, "display_alert_panel", display_alert_panel, 2);
}
