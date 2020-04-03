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
 * $Id: HinPNGIcon.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBPNGICON_H
#define FXRBPNGICON_H

class HinPNGIcon : public FXPNGIcon {
  FXDECLARE(HinPNGIcon)
protected:
  HinPNGIcon(){}
#include "HinObjectVirtuals.h"
#include "HinIdVirtuals.h"
#include "HinDrawableVirtuals.h"
#include "HinImageVirtuals.h"
public:
  /// Construct an icon from memory stream formatted in PNG format
  HinPNGIcon(FXApp *a,const void *pix=NULL,FXColor clr=FXRGB(192,192,192),FXuint opts=0,FXint w=1,FXint h=1) : FXPNGIcon(a,pix,clr,opts,w,h){
    HinRegisterAppSensitiveObject(this);
    }

  // Destructor
  virtual ~HinPNGIcon(){
    HinUnregisterRubyObj(this);
    HinUnregisterAppSensitiveObject(this);
    }

  // Mark dependencies for the GC
  static void markfunc(FXPNGIcon* self);
  };

#endif
