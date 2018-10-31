#include <CoreFoundation/CoreFoundation.h>
#include <objc/objc-runtime.h>
#include <objc/objc.h>
#include <ruby.h>

// Guide: https://github.com/ruby/ruby/blob/trunk/doc/extension.rdoc
int
NSRunAlertPanel(CFStringRef strTitle,
                CFStringRef strMsg,
                CFStringRef strButton1,
                CFStringRef strButton2,
                CFStringRef strButton3,
                ...);

VALUE
display_alert_panel(VALUE self, VALUE title, VALUE message)
{
  Check_Type(title, T_STRING);
  Check_Type(message, T_STRING);

  char* title_ptr = RSTRING_PTR(title);
  char* message_ptr = RSTRING_PTR(message);

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

  // CFSTR is a macro to expand literal C string to CFStringRef
  // CFStringCreateWithCString is for converting C string pointer to CFStringRef
  NSRunAlertPanel(
    CFStringCreateWithCString(NULL, title_ptr, kCFStringEncodingUTF8),
    CFStringCreateWithCString(NULL, message_ptr, kCFStringEncodingUTF8),
    CFSTR("OK"),
    NULL,
    NULL);
  objc_msgSend(pool, sel_registerName("release"));
  return Qnil;
}

VALUE
nimo_hello()
{
  printf("Hello, World!\n");
  // setDesktopImageURL("/Users/gadhikari/Wallpapers/eXpresso.jpg", 1, NULL);
  return Qnil;
}

void
Init_nimo(void)
{
  VALUE cNimo = rb_define_module("Nimo");
  VALUE cMacOsHelpers = rb_define_class_under(cNimo, "Macintosh", rb_cObject);
  rb_define_singleton_method(cMacOsHelpers, "hello", nimo_hello, 0);
  rb_define_singleton_method(
    cMacOsHelpers, "display_alert_panel", display_alert_panel, 2);
}
