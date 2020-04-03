/***********************************************************************
 * Hinamori -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001-2009 by Lyle Johnson. All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * For further information please contact the author by e-mail
 * at "lyle@lylejohnson.name".
 ***********************************************************************/

/***********************************************************************
 * $Id: HinSpinner.h 2238 2005-11-09 13:41:54Z lyle $
 ***********************************************************************/

#ifndef FXRBSPINNER_H
#define FXRBSPINNER_H

#define DECLARE_FXSPINNER_STUBS(klass) \
inline void klass ## _setValue(klass* self,FXint value,FXbool notify){ \
  self->klass::setValue(value,notify); \
  }


#define IMPLEMENT_FXSPINNER_STUBS(cls) \
  void cls::setValue(FXint value,FXbool notify){ \
    HinCallVoidMethod(this,"setValue",value,notify); \
    }


class HinSpinner : public FXSpinner {
  FXDECLARE(HinSpinner)
protected:
  HinSpinner(){}
#include "HinObjectVirtuals.h"
#include "HinIdVirtuals.h"
#include "HinDrawableVirtuals.h"
#include "HinWindowVirtuals.h"
#include "HinSpinnerVirtuals.h"
public:
  /// Construct a spinner
  HinSpinner(FXComposite *p,FXint cols,FXObject *tgt=NULL,FXSelector sel=0,FXuint opts=SPIN_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD) : FXSpinner(p,cols,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb){}

  // Destructor
  virtual ~HinSpinner(){
    HinUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXSpinner* self);
  };

#endif
