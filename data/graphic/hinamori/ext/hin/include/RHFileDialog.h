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
 * $Id: HinFileDialog.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBFILEDIALOG_H
#define FXRBFILEDIALOG_H

class HinFileDialog : public FXFileDialog {
  FXDECLARE(HinFileDialog)
protected:
  HinFileDialog(){}
#include "HinObjectVirtuals.h"
#include "HinIdVirtuals.h"
#include "HinDrawableVirtuals.h"
#include "HinWindowVirtuals.h"
#include "HinTopWindowVirtuals.h"
#include "HinDialogBoxVirtuals.h"
public:
  /// Construct file dialog box
  HinFileDialog(FXWindow* owner,const FXString& name,FXuint opts=0,FXint x=0,FXint y=0,FXint w=500,FXint h=300) : FXFileDialog(owner,name,opts,x,y,w,h){}

  /// Construct free-floating file dialog box
  HinFileDialog(FXApp* a,const FXString& name,FXuint opts=0,FXint x=0,FXint y=0,FXint w=500,FXint h=300) : FXFileDialog(a,name,opts,x,y,w,h){}

  // Mark dependencies for the GC
  static void markfunc(FXFileDialog* self);

  // Destructor
  virtual ~HinFileDialog(){
    HinUnregisterRubyObj(this);
    }
  };

#endif
