#include <stdio.h>
#include <string.h>
#include <ruby.h>
#include <ruby/intern.h>

// This is a module in C for Ruby

//       Methods
static VALUE world(VALUE self) {
    // Return Sting
    char* n = "Hola";
    VALUE hh = rb_str_new2(n);
    return hh;
}

static VALUE history(VALUE self) {
    // Return Integer
    //printf("Hola");
    //return Qfalse;
    int n = 1;
    VALUE hh = rb_int_new(n);
    return hh;
}
/*
// XXX: Unstable (not found)
static VALUE legend(VALUE self) {
    // Return Integer
    //printf("Hola");
    //return Qfalse;
    int n[] = {1,2,3};
    VALUE hh = rb_ary_join(n);
    return hh;
}
*/
/* 
Basic Types
c      |   Ruby
Qnil   | nil, 
Qfalse | false
Qtrue  | true
*/
/*extern "C" {
#if 0
}
rb_check_array_type
rb_ary_join
to_ary

rb_ary_new
rb_ary_push
rb_ary_aref1
#include "ruby/intern.h"
*/

// The initialization method for this module
void Init_welcome_c() {  // Name for require: welcome_c; Init_ is a special keyword
    // Neme module HelloC
    VALUE Hello = rb_define_module("HelloC");
    rb_define_method(Hello, "world", world, 0);
    rb_define_method(Hello, "history", history, 0);
    //rb_define_method(Hello, "legend", legend, 0);
    // rb_define_singleton_method  // define module method
}