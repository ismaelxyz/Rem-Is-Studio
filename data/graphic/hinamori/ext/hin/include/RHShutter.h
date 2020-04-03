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
 * $Id: HinShutter.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBSHUTTER_H
#define FXRBSHUTTER_H

class HinShutterItem : public FXShutterItem {
  FXDECLARE(HinShutterItem)
protected:
  HinShutterItem(){}
#include "HinObjectVirtuals.h"
#include "HinIdVirtuals.h"
#include "HinDrawableVirtuals.h"
#include "HinWindowVirtuals.h"
public:
  /// Constructor
  HinShutterItem(FXShutter *p,const FXString& text,FXIcon* icon=NULL,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING) : FXShutterItem(p,text,icon,opts,x,y,w,h,pl,pr,pt,pb,hs,vs){}

  // Destructor
  virtual ~HinShutterItem(){
    HinUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXShutterItem* self);
  };


#define DECLARE_FXSHUTTER_STUBS(klass) \
inline void klass ## _setCurrent(klass* self,FXint panel){ \
  self->klass::setCurrent(panel); \
  }


#define IMPLEMENT_FXSHUTTER_STUBS(cls) \
  void cls::setCurrent(FXint panel){ \
    HinCallVoidMethod(this,"setCurrent",panel); \
    }


class HinShutter : public FXShutter {
  FXDECLARE(HinShutter)
protected:
  HinShutter(){}
#include "HinObjectVirtuals.h"
#include "HinIdVirtuals.h"
#include "HinDrawableVirtuals.h"
#include "HinWindowVirtuals.h"
#include "HinShutterVirtuals.h"
public:
  /// Constructor
  HinShutter(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_SPACING,FXint pr=DEFAULT_SPACING,FXint pt=DEFAULT_SPACING,FXint pb=DEFAULT_SPACING,FXint hs=DEFAULT_SPACING,FXint vs=DEFAULT_SPACING) : FXShutter(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb,hs,vs){}

  // Destructor
  virtual ~HinShutter(){
    HinUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXShutter* self);
  };

#endif
