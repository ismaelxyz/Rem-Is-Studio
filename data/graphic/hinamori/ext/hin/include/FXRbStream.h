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
 * $Id: HinStream.h 2344 2006-02-12 21:19:36Z lyle $
 ***********************************************************************/

#ifndef FXRBSTREAM_H
#define FXRBSTREAM_H

#define DECLARE_FXSTREAM_STUBS(klass) \
inline bool klass ## _close(klass* self){ \
  return self->klass::close(); \
  } \
inline bool klass ## _flush(klass* self){ \
  return self->klass::flush(); \
  } \
inline bool klass ## _position(klass* self,FXlong p,FXWhence whence){ \
  return self->klass::position(p,whence); \
  }


#define IMPLEMENT_FXSTREAM_STUBS(cls) \
  bool cls::close(){ \
    return HinCallBoolMethod(this,"close"); \
    } \
  bool cls::flush(){ \
    return HinCallBoolMethod(this,"flush"); \
    } \
  bool cls::position(FXlong p,FXWhence whence){ \
    return HinCallBoolMethod(this,"setPosition",p,whence); \
    }


class HinStream : public FXStream {
#include "HinStreamVirtuals.h"
public:
  /// Constructor
  HinStream(const FXObject* cont=NULL) : FXStream(cont){}

  // Mark dependencies for the GC
  static void markfunc(FXStream* self);

  // Destructor
  virtual ~HinStream(){
    HinUnregisterRubyObj(this);
    }
  };


class HinFileStream : public FXFileStream {
#include "HinStreamVirtuals.h"
public:
  /// Constructor
  HinFileStream(const FXObject* cont=NULL) : FXFileStream(cont){}

  // Mark dependencies for the GC
  static void markfunc(FXFileStream* self);

  // Destructor
  virtual ~HinFileStream(){
    HinUnregisterRubyObj(this);
    }
  };


class HinMemoryStream : public FXMemoryStream {
#include "HinStreamVirtuals.h"
public:
  /// Create memory store
  HinMemoryStream(const FXObject* cont=NULL) : FXMemoryStream(cont){}

  // Mark dependencies for the GC
  static void markfunc(FXMemoryStream* self);

  // Destructor
  virtual ~HinMemoryStream(){
    HinUnregisterRubyObj(this);
    }
  };

#endif
