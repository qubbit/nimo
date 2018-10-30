require "mkmf"

abort "missing malloc()" unless have_func "malloc"
abort "missing free()"   unless have_func "free"
abort "no cocoa" unless have_framework("Cocoa")

create_makefile "nimo/nimo"
