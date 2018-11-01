require "mkmf"

abort "missing malloc()" unless have_func "malloc"
abort "missing free()"   unless have_func "free"

if RUBY_PLATFORM =~ /darwin/
  abort "no cocoa" unless have_framework("Cocoa")
end

create_header
create_makefile "nimo/nimo"
