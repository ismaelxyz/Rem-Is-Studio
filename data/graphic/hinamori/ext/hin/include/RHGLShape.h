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
 * $Id: HinGLShape.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBGLSHAPE_H
#define FXRBGLSHAPE_H

#define DECLARE_FXGLSHAPE_STUBS(klass,subklass) \
inline void klass ## _drawshape(klass* self,FXGLViewer* viewer){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<subklass*>(self)->_drawshape(viewer); \
  }

#define IMPLEMENT_FXGLSHAPE_STUBS(klass,superklass) \
  void klass::drawshape(FXGLViewer* viewer){ \
    HinCallVoidMethod(this,"drawshape",viewer); \
    } \
  void klass::_drawshape(FXGLViewer* viewer){ \
    superklass::drawshape(viewer); \
    }

class HinGLShape : public FXGLShape {
  FXDECLARE(HinGLShape)
protected:
  HinGLShape(){}
#include "HinObjectVirtuals.h"
#include "HinGLObjectVirtuals.h"
#include "HinGLShapeVirtuals.h"
public:
  /// Construct with specified origin and options
  HinGLShape(FXfloat x,FXfloat y,FXfloat z,FXuint opts) : FXGLShape(x,y,z,opts){}

  /// Construct with specified origin, options and front and back materials
  HinGLShape(FXfloat x,FXfloat y,FXfloat z,FXuint opts,const FXMaterial& front,const FXMaterial& back) : FXGLShape(x,y,z,opts,front,back){}

  // Identify sub-object given path
  virtual FXGLObject* identify(FXuint* path,FXint n);

  // Get position
  FXVec3f getPosition() const { return position; }

  // Set position
  void setPosition(const FXVec3f& pos){ position=pos; }

  // Set the range
  void setRange(const FXRangef& box){
    range=box;
    }

  // Mark dependencies for the GC
  static void markfunc(FXGLShape* self);

  // Destructor
  virtual ~HinGLShape(){
    HinUnregisterRubyObj(this);
    }
  };

#endif
