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
 * $Id: HinMDIButton.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBMDIMENU_H
#define FXRBMDIMENU_H

class HinMDIDeleteButton : public FXMDIDeleteButton {
  FXDECLARE(HinMDIDeleteButton)
protected:
  HinMDIDeleteButton(){}
#include "HinObjectVirtuals.h"
#include "HinIdVirtuals.h"
#include "HinDrawableVirtuals.h"
#include "HinWindowVirtuals.h"
public:
  /// Constructor
  HinMDIDeleteButton(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_RAISED,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXMDIDeleteButton(p,tgt,sel,opts,x,y,w,h){}

  // Destructor
  virtual ~HinMDIDeleteButton(){
    HinUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXMDIDeleteButton* self);
  };


class HinMDIRestoreButton : public FXMDIRestoreButton {
  FXDECLARE(HinMDIRestoreButton)
protected:
  HinMDIRestoreButton(){}
#include "HinObjectVirtuals.h"
#include "HinIdVirtuals.h"
#include "HinDrawableVirtuals.h"
#include "HinWindowVirtuals.h"
public:
  /// Constructor
  HinMDIRestoreButton(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_RAISED,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXMDIRestoreButton(p,tgt,sel,opts,x,y,w,h){}

  // Destructor
  virtual ~HinMDIRestoreButton(){
    HinUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXMDIRestoreButton* self);
  };


class HinMDIMinimizeButton : public FXMDIMinimizeButton {
  FXDECLARE(HinMDIMinimizeButton)
protected:
  HinMDIMinimizeButton(){}
#include "HinObjectVirtuals.h"
#include "HinIdVirtuals.h"
#include "HinDrawableVirtuals.h"
#include "HinWindowVirtuals.h"
public:
  /// Constructor
  HinMDIMinimizeButton(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_RAISED,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXMDIMinimizeButton(p,tgt,sel,opts,x,y,w,h){}

  // Destructor
  virtual ~HinMDIMinimizeButton(){
    HinUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXMDIMinimizeButton* self);
  };


class HinMDIMaximizeButton : public FXMDIMaximizeButton {
  FXDECLARE(HinMDIMaximizeButton)
protected:
  HinMDIMaximizeButton(){}
#include "HinObjectVirtuals.h"
#include "HinIdVirtuals.h"
#include "HinDrawableVirtuals.h"
#include "HinWindowVirtuals.h"
public:
  /// Constructor
  HinMDIMaximizeButton(FXComposite* p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_RAISED,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXMDIMaximizeButton(p,tgt,sel,opts,x,y,w,h){}

  // Destructor
  virtual ~HinMDIMaximizeButton(){
    HinUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXMDIMaximizeButton* self);
  };


class HinMDIWindowButton : public FXMDIWindowButton {
  FXDECLARE(HinMDIWindowButton)
protected:
  HinMDIWindowButton(){}
#include "HinObjectVirtuals.h"
#include "HinIdVirtuals.h"
#include "HinDrawableVirtuals.h"
#include "HinWindowVirtuals.h"
public:
  /// Constructor
  HinMDIWindowButton(FXComposite* p,FXPopup* pup,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=FRAME_RAISED,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXMDIWindowButton(p,pup,tgt,sel,opts,x,y,w,h){}

  // Destructor
  virtual ~HinMDIWindowButton(){
    HinUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXMDIWindowButton* self);
  };


class HinMDIMenu : public FXMDIMenu {
  FXDECLARE(HinMDIMenu)
protected:
  HinMDIMenu(){}
#include "HinObjectVirtuals.h"
#include "HinIdVirtuals.h"
#include "HinDrawableVirtuals.h"
#include "HinWindowVirtuals.h"
#include "HinPopupVirtuals.h"
public:
  /// Construct MDI menu
  HinMDIMenu(FXWindow *owner,FXObject* tgt=NULL) : FXMDIMenu(owner,tgt){}

  // Destructor
  virtual ~HinMDIMenu(){
    HinUnregisterRubyObj(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXMDIMenu* self);
  };

#endif
