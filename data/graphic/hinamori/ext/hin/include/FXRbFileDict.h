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
 * $Id: HinFileDict.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBFILEDICT_H
#define FXRBFILEDICT_H

/// Icon dictionary
class HinIconDict : public FXIconDict {
  FXDECLARE(HinIconDict)
protected:
  HinIconDict(){}
#include "HinObjectVirtuals.h"
public:
  /// Construct an icon dictionary, with given path
  HinIconDict(FXApp* a,const FXString& p=defaultIconPath) : FXIconDict(a,p){}

  // Mark dependencies for the GC
  static void markfunc(FXIconDict* self);

  // Destructor
  virtual ~HinIconDict(){
    HinUnregisterRubyObj(this);
    }
  };


#define DECLARE_FXFILEDICT_STUBS(klass) \
inline FXFileAssoc* klass ## _findFileBinding(klass* self,const FXchar* pathname){ \
  return self->klass::findFileBinding(pathname); \
  } \
inline FXFileAssoc* klass ## _findDirBinding(klass* self,const FXchar* pathname){ \
  return self->klass::findDirBinding(pathname); \
  } \
inline FXFileAssoc* klass ## _findExecBinding(klass* self,const FXchar* pathname){ \
  return self->klass::findExecBinding(pathname); \
  }


#define IMPLEMENT_FXFILEDICT_STUBS(cls) \
  FXFileAssoc* cls::findFileBinding(const FXchar* pathname){ \
    return HinCallFileAssocMethod(this,"findFileBinding",pathname); \
    } \
  FXFileAssoc* cls::findDirBinding(const FXchar* pathname){ \
    return HinCallFileAssocMethod(this,"findDirBinding",pathname); \
    } \
  FXFileAssoc* cls::findExecBinding(const FXchar* pathname){ \
    return HinCallFileAssocMethod(this,"findExecBinding",pathname); \
    }


/// File Association dictionary
class HinFileDict : public FXFileDict {
  FXDECLARE(HinFileDict)
protected:
  HinFileDict(){}
#include "HinObjectVirtuals.h"
#include "HinFileDictVirtuals.h"
public:
  /**
  * Construct a dictionary mapping file-extension to file associations,
  * using the application registry settings as a source for the bindings.
  */
  HinFileDict(FXApp* a) : FXFileDict(a){}

  /**
  * Construct a dictionary mapping file-extension to file associations,
  * using the specified settings database as a source for the bindings.
  */
  HinFileDict(FXApp* a,FXSettings* db) : FXFileDict(a,db){}

  // Mark dependencies for the GC
  static void markfunc(FXFileDict* self);

  // Destructor
  virtual ~HinFileDict(){
    HinUnregisterRubyObj(this);
    }
  };


#endif
