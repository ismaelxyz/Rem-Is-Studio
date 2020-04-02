//#include <stdio.h>
#include <string.h>
#include <ruby.h>



VALUE world(VALUE self) {
    return Qfalse;
}

// The initialization method for this module
void Init_saludar() {
    VALUE HelloC = rb_define_module("Saluda");
    rb_define_singleton_method(HelloC, "world", world, 0);
}