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
 * $Id: HinIconList.h 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#ifndef FXRBICONLIST_H
#define FXRBICONLIST_H

#define DECLARE_FXICONITEM_STUBS(klass,subklass) \
inline void klass ## _draw(const klass* self,const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<const subklass*>(self)->public_draw(list,dc,x,y,w,h); \
  } \
inline FXint klass ## _hitItem(const klass* self,const FXIconList* list,FXint rx,FXint ry,FXint rw,FXint rh){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  return dynamic_cast<const subklass*>(self)->public_hitItem(list,rx,ry,rw,rh); \
  } \
inline void klass ## _drawBigIcon(const klass* self,const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<const subklass*>(self)->public_drawBigIcon(list,dc,x,y,w,h); \
  } \
inline void klass ## _drawMiniIcon(const klass* self,const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<const subklass*>(self)->public_drawMiniIcon(list,dc,x,y,w,h); \
  } \
inline void klass ## _drawDetails(const klass* self,const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<const subklass*>(self)->public_drawDetails(list,dc,x,y,w,h); \
  } \
inline void klass ## _setText(klass* self,const FXString& text){ \
  self->klass::setText(text); \
  } \
inline void klass ## _setBigIcon(klass* self,FXIcon* icn,FXbool owned){ \
  self->klass::setBigIcon(icn,owned); \
  } \
inline void klass ## _setMiniIcon(klass* self,FXIcon* icn,FXbool owned){ \
  self->klass::setMiniIcon(icn,owned); \
  } \
inline void klass ## _setFocus(klass* self,FXbool focus){ \
  self->klass::setFocus(focus); \
  } \
inline void klass ## _setSelected(klass* self,FXbool selected){ \
  self->klass::setSelected(selected); \
  } \
inline void klass ## _setEnabled(klass* self,FXbool enabled){ \
  self->klass::setEnabled(enabled); \
  } \
inline void klass ## _setDraggable(klass* self,FXbool draggable){ \
  self->klass::setDraggable(draggable); \
  } \
inline FXint klass ## _getWidth(const klass* self,const FXIconList* list){ \
  return self->klass::getWidth(list); \
  } \
inline FXint klass ## _getHeight(const klass* self,const FXIconList* list){ \
  return self->klass::getHeight(list); \
  } \
inline void klass ## _create(klass* self){ \
  self->klass::create(); \
  } \
inline void klass ## _detach(klass* self){ \
  self->klass::detach(); \
  } \
inline void klass ## _destroy(klass* self){ \
  self->klass::destroy(); \
  }


#define IMPLEMENT_FXICONITEM_STUBS(klass,superklass) \
  void klass::draw(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const { \
    HinCallVoidMethod(this,"draw",list,dc,x,y,w,h); \
    } \
  void klass::public_draw(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const { \
    superklass::draw(list,dc,x,y,w,h); \
    } \
  FXint klass::hitItem(const FXIconList* list,FXint rx,FXint ry,FXint rw,FXint rh) const { \
    return HinCallIntMethod(this,"hitItem",list,rx,ry,rw,rh); \
    } \
  FXint klass::public_hitItem(const FXIconList* list,FXint rx,FXint ry,FXint rw,FXint rh) const { \
    return superklass::hitItem(list,rx,ry,rw,rh); \
    } \
  void klass::drawBigIcon(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const { \
    HinCallVoidMethod(this,"drawBigIcon",list,dc,x,y,w,h); \
    } \
  void klass::public_drawBigIcon(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const { \
    superklass::drawBigIcon(list,dc,x,y,w,h); \
    } \
  void klass::drawMiniIcon(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const { \
    HinCallVoidMethod(this,"drawMiniIcon",list,dc,x,y,w,h); \
    } \
  void klass::public_drawMiniIcon(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const { \
    superklass::drawMiniIcon(list,dc,x,y,w,h); \
    } \
  void klass::drawDetails(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const { \
    HinCallVoidMethod(this,"drawDetails",list,dc,x,y,w,h); \
    } \
  void klass::public_drawDetails(const FXIconList* list,FXDC& dc,FXint x,FXint y,FXint w,FXint h) const { \
    superklass::drawDetails(list,dc,x,y,w,h); \
    } \
  void klass::setText(const FXString& txt){ \
    HinCallVoidMethod(this,"setText",txt); \
    } \
  void klass::setBigIcon(FXIcon* icn,FXbool owned){ \
    HinCallVoidMethod(this,"setBigIcon",icn,owned); \
    } \
  void klass::setMiniIcon(FXIcon* icn,FXbool owned){ \
    HinCallVoidMethod(this,"setMiniIcon",icn,owned); \
    } \
  void klass::setFocus(FXbool focus){ \
    HinCallVoidMethod(this,"setFocus",focus); \
    } \
  void klass::setSelected(FXbool selected){ \
    HinCallVoidMethod(this,"setSelected",selected); \
    } \
  void klass::setEnabled(FXbool enabled){ \
    HinCallVoidMethod(this,"setEnabled",enabled); \
    } \
  void klass::setDraggable(FXbool draggable){ \
    HinCallVoidMethod(this,"setDraggable",draggable); \
    } \
  FXint klass::getWidth(const FXIconList* list) const { \
    return HinCallIntMethod(this,"getWidth",list); \
    } \
  FXint klass::getHeight(const FXIconList* list) const { \
    return HinCallIntMethod(this,"getHeight",list); \
    } \
  void klass::create(){ \
    HinCallVoidMethod(this,"create"); \
    } \
  void klass::detach(){ \
    HinCallVoidMethod(this,"detach"); \
    } \
  void klass::destroy(){ \
    HinCallVoidMethod(this,"destroy"); \
    }


class HinIconItem : public FXIconItem {
  FXDECLARE(HinIconItem)
protected:
  HinIconItem(){}
#include "HinObjectVirtuals.h"
#include "HinIconItemVirtuals.h"
public:
  // Is this icon item owned by an FXIconList yet?
  FXbool owned;
public:
  // Constructor
  HinIconItem(const FXString& text,FXIcon* bi=NULL,FXIcon* mi=NULL,void* ptr=NULL) : FXIconItem(text,bi,mi,ptr),owned(FALSE){}

  // Mark dependencies for the GC
  static void markfunc(FXIconItem* self);

  // Destroy this object if it's not owned
  static void freefunc(FXIconItem* self);

  // Destructor
  virtual ~HinIconItem(){
    HinUnregisterRubyObj(this);
    }
  };


#define DECLARE_FXICONLIST_STUBS(klass) \
inline FXbool klass ## _selectItem(klass* self,FXint index,FXbool notify){ \
  return self->klass::selectItem(index,notify); \
  } \
inline FXbool klass ## _deselectItem(klass* self,FXint index,FXbool notify){ \
  return self->klass::deselectItem(index,notify); \
  } \
inline FXbool klass ## _toggleItem(klass* self,FXint index,FXbool notify){ \
  return self->klass::toggleItem(index,notify); \
  } \
inline FXbool klass ## _selectInRectangle(klass* self,FXint x,FXint y,FXint w,FXint h,FXbool notify){ \
  return self->klass::selectInRectangle(x,y,w,h,notify); \
  } \
inline FXbool klass ## _extendSelection(klass* self,FXint index,FXbool notify){ \
  return self->klass::extendSelection(index,notify); \
  } \
inline FXbool klass ## _killSelection(klass* self,FXbool notify){ \
  return self->klass::killSelection(notify); \
  } \
inline void klass ## _setCurrentItem(klass* self,FXint index,FXbool notify){ \
  self->klass::setCurrentItem(index,notify); \
  } \
inline FXint klass ## _getItemAt(const klass* self,FXint x,FXint y){ \
  return self->klass::getItemAt(x,y); \
  } \
inline void klass ## _makeItemVisible(klass* self,FXint index){ \
  self->klass::makeItemVisible(index); \
  } \
inline FXbool klass ## _enableItem(klass* self,FXint index){ \
  return self->klass::enableItem(index); \
  } \
inline FXbool klass ## _disableItem(klass* self,FXint index){ \
  return self->klass::disableItem(index); \
  }


#define IMPLEMENT_FXICONLIST_STUBS(cls) \
  FXbool cls::selectItem(FXint index,FXbool notify){ \
    return HinCallBoolMethod(this,"selectItem",index,notify); \
    } \
  FXbool cls::deselectItem(FXint index,FXbool notify){ \
    return HinCallBoolMethod(this,"deselectItem",index,notify); \
    } \
  FXbool cls::toggleItem(FXint index,FXbool notify){ \
    return HinCallBoolMethod(this,"toggleItem",index,notify); \
    } \
  FXbool cls::selectInRectangle(FXint x,FXint y,FXint w,FXint h,FXbool notify){ \
    return HinCallBoolMethod(this,"selectInRectangle",x,y,w,h,notify); \
    } \
  FXbool cls::extendSelection(FXint index,FXbool notify){ \
    return HinCallBoolMethod(this,"extendSelection",index,notify); \
    } \
  FXbool cls::killSelection(FXbool notify){ \
    return HinCallBoolMethod(this,"killSelection",notify); \
    } \
  void cls::setCurrentItem(FXint index,FXbool notify){ \
    HinCallVoidMethod(this,"setCurrentItem",index,notify); \
    } \
  FXint cls::getItemAt(FXint x,FXint y) const { \
    return HinCallIntMethod(this,"getItemAt",x,y); \
    } \
  void cls::makeItemVisible(FXint index){ \
    HinCallVoidMethod(this,"makeItemVisible",index); \
    } \
  FXbool cls::enableItem(FXint index){ \
    return HinCallBoolMethod(this,"enableItem",index); \
    } \
  FXbool cls::disableItem(FXint index){ \
    return HinCallBoolMethod(this,"disableItem",index); \
    }


class HinIconList : public FXIconList {
  FXDECLARE(HinIconList)
protected:
  HinIconList(){}
#include "HinObjectVirtuals.h"
#include "HinIdVirtuals.h"
#include "HinDrawableVirtuals.h"
#include "HinWindowVirtuals.h"
#include "HinScrollAreaVirtuals.h"
#include "HinIconListVirtuals.h"
public:
  /// Construct icon list
  HinIconList(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=ICONLIST_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0) : FXIconList(p,tgt,sel,opts,x,y,w,h){
    setSortFunc(HinIconList::sortFunc);
    }

  // Mark dependencies for the GC
  static void markfunc(FXIconList* self);

  // Unregister objects that this icon list owns and is about to destroy
  static void unregisterOwnedObjects(FXIconList *pIconList);

  // Sort function stand-in
  static FXint sortFunc(const FXIconItem* a,const FXIconItem* b);

  // Destructor
  virtual ~HinIconList(){
    HinIconList::unregisterOwnedObjects(this);
    HinUnregisterRubyObj(this);
    }
  };

#endif
