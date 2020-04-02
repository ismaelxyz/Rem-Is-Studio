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
 * $Id: HinXBMImage.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBXBMIMAGE_H
#define FXRBXBMIMAGE_H

class HinXBMImage : public FXXBMImage {
  FXDECLARE(HinXBMImage)
protected:
  HinXBMImage(){}
#include "HinObjectVirtuals.h"
#include "HinIdVirtuals.h"
#include "HinDrawableVirtuals.h"
#include "HinImageVirtuals.h"
public:
  /// Construct image from memory stream formatted in X Bitmap format
  HinXBMImage(FXApp* a,const FXuchar *pixels=NULL,const FXuchar *mask=NULL,FXuint opts=0,FXint w=1,FXint h=1) : FXXBMImage(a,pixels,mask,opts,w,h){
    HinRegisterAppSensitiveObject(this);
    }

  // Destructor
  virtual ~HinXBMImage(){
    HinUnregisterRubyObj(this);
    HinUnregisterAppSensitiveObject(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXXBMImage* self);
  };

#endif
