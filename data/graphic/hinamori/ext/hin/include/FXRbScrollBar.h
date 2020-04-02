/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
 * Copyright (c) 2001 by J. Lyle Johnson. All Rights Reserved.
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
 * $Id: HinScrollBar.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBSCROLLBAR_H
#define FXRBSCROLLBAR_H

class HinScrollBar : public FXScrollBar {
  FXDECLARE(HinScrollBar)
protected:
  HinScrollBar(){}
#include "HinObjectVirtuals.h"
#include "HinIdVirtuals.h"
#include "HinDrawableVirtuals.h"
#include "HinWindowVirtuals.h"
public:
  /// Construct scroll bar
  HinScrollBar(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=SCROLLBAR_VERTICAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXScrollBar(p,tgt,sel,opts,x,y,w,h){}

  // Destructor
  virtual ~HinScrollBar(){
    HinUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXScrollBar* self);
  };


class HinScrollCorner : public FXScrollCorner {
  FXDECLARE(HinScrollCorner)
protected:
  HinScrollCorner(){}
#include "HinObjectVirtuals.h"
#include "HinIdVirtuals.h"
#include "HinDrawableVirtuals.h"
#include "HinWindowVirtuals.h"
public:
  /// Constructor
  HinScrollCorner(FXComposite* p) : FXScrollCorner(p){}

  // Destructor
  virtual ~HinScrollCorner(){
    HinUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXScrollCorner* self);
  };

#endif
