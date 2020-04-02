/***********************************************************************
 * FXRuby -- the Ruby language bindings for the FOX GUI toolkit.
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
 * $Id: HinScintilla.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBSCINTILLA_H
#define FXRBSCINTILLA_H

class HinScintilla : public FXScintilla {
  FXDECLARE(HinScintilla)
protected:
  HinScintilla(){}
#include "HinObjectVirtuals.h"
#include "HinIdVirtuals.h"
#include "HinDrawableVirtuals.h"
#include "HinWindowVirtuals.h"
#include "HinScrollAreaVirtuals.h"
public:
  /// Constructor
  HinScintilla(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXScintilla(p,tgt,sel,opts,x,y,w,h){}

  // Mark dependencies for garbage collector
  static void markfunc(FXScintilla* self);

  // Destructor
  virtual ~HinScintilla(){
    HinUnregisterRubyObj(this);
    }
  };

#endif
