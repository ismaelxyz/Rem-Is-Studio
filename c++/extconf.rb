require 'mkmf'
#create_makefile('saludar')

gem 'mini_portile2', '~>2.1'
require 'mini_portile2'

execute "compile", "hello"

do_rake_compiler_setup

if RbConfig::MAKEFILE_CONFIG['CC'] =~ /gcc/
  $CXXFLAGS += " -Wno-unused-function"
  $CXXFLAGS += " -Wno-maybe-uninitialized"
end

# Last step: build the makefile
create_header
create_makefile("saludar")















__END__
#ifndef FXRBACCELTABLE_H
#define FXRBACCELTABLE_H

class HinAccelTable : public FXAccelTable {
    FXDECLARE(HinAccelTable)
  #include "HinObjectVirtuals.h"
  public:
    // Constructor
    HinAccelTable(){}
  
    // Destructor
    virtual ~HinAccelTable(){
      HinUnregisterRubyObj(this);
      }
  
    // Mark dependencies for GC
    static void markfunc(FXAccelTable* accelTable);
    };
  
  #endif
  inline VALUE to_ruby(FXFontDesc* fontdesc){
    return HinNewPointerObj(reinterpret_cast<void*>(fontdesc),HinTypeQuery("FXFontDesc *"));
    }