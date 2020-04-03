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
 * $Id: HinPCXImage.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBPCXIMAGE_H
#define FXRBPCXIMAGE_H

class HinPCXImage : public FXPCXImage {
  FXDECLARE(HinPCXImage)
protected:
  HinPCXImage(){}
#include "HinObjectVirtuals.h"
#include "HinIdVirtuals.h"
#include "HinDrawableVirtuals.h"
#include "HinImageVirtuals.h"
public:
  /// Construct an image from memory stream formatted as PCX
  HinPCXImage(FXApp* a,const void *pix=NULL,FXuint opts=0,FXint w=1,FXint h=1) : FXPCXImage(a,pix,opts,w,h){
    HinRegisterAppSensitiveObject(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXPCXImage* self);

  // Destructor
  virtual ~HinPCXImage(){
    HinUnregisterRubyObj(this);
    HinUnregisterAppSensitiveObject(this);
    }
  };

#endif
