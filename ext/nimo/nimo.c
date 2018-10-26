#include <ruby.h>

VALUE nimo_hello() {
  printf("Hello, World!");
  return Qnil;
}

void Init_nimo(void) {
  VALUE cNimo = rb_define_class("Nimo", rb_cObject);

  rb_define_method(cNimo, "hello", nimo_hello, 1);
  rb_define_singleton_method(cNimo, "h", nimo_hello, 0);
}
