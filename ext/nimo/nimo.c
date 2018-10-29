#include <CoreFoundation/CoreFoundation.h>
#include <objc/objc-runtime.h>
#include <objc/objc.h>
#include <ruby.h>

// Guide: https://github.com/ruby/ruby/blob/trunk/doc/extension.rdoc
// void rb_define_singleton_method(VALUE object, const char *name,
//                                 VALUE (*func)(ANYARGS), int argc)

VALUE display_alert_panel(T_STRING title, T_STRING message) {
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

  NSRunAlertPanel(CFSTR(title), CFSTR(message), CFSTR("OK"), NULL, NULL);
  objc_msgSend(pool, sel_registerName("release"));
}

VALUE nimo_hello() {
  printf("Hello, World!\n");
  // setDesktopImageURL("/Users/gadhikari/Wallpapers/eXpresso.jpg", 1, NULL);
  printf("%p", pool);

  return Qnil;
}

void Init_nimo(void) {
  VALUE cNimo = rb_define_class("Nimo", rb_cObject);

  rb_define_singleton_method(cNimo, "hello", nimo_hello, 0);
  rb_define_singleton_method(cNimo, "display_alert_message", nimo_hello, 2);
}
