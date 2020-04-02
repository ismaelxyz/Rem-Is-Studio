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
 * $Id: HinDirList.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBDIRLIST_H
#define FXRBDIRLIST_H

class HinDirItem : public FXDirItem {
  FXDECLARE(HinDirItem)
protected:
  HinDirItem(){}
#include "HinObjectVirtuals.h"
#include "HinTreeItemVirtuals.h"
public:
  // Is this directory item owned by an FXDirList yet?
  FXbool owned;
public:
  // Constructor
  HinDirItem(const FXString& text,FXIcon* oi=NULL,FXIcon* ci=NULL,void* ptr=NULL) : FXDirItem(text,oi,ci,ptr),owned(FALSE){}

  // Mark dependencies for the GC
  static void markfunc(FXDirItem* self);

  // Destroy this object if it's not owned
  static void freefunc(FXDirItem* self);

  // Destructor
  virtual ~HinDirItem(){
    HinUnregisterRubyObj(this);
    }
  };


class HinDirList : public FXDirList {
  FXDECLARE(HinDirList)
protected:
  HinDirList(){}
#include "HinObjectVirtuals.h"
#include "HinIdVirtuals.h"
#include "HinDrawableVirtuals.h"
#include "HinWindowVirtuals.h"
#include "HinScrollAreaVirtuals.h"
#include "HinTreeListVirtuals.h"
public:
  /// Construct a directory list
  HinDirList(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXDirList(p,tgt,sel,opts,x,y,w,h){}

  // Mark dependencies for the GC
  static void markfunc(FXDirList* self);

  // Destructor
  virtual ~HinDirList(){
    HinUnregisterRubyObj(this);
    }
  };

#endif
