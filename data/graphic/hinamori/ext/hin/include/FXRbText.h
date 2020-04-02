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
 * $Id: HinText.h 2395 2006-04-22 17:27:36Z lyle $
 ***********************************************************************/

#ifndef FXRBTEXT_H
#define FXRBTEXT_H

#define DECLARE_FXTEXT_STUBS(klass,subklass) \
inline void klass ## _eraseCursorOverhang(klass* self){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<subklass*>(self)->public_eraseCursorOverhang(); \
  } \
inline void klass ## _drawCursor(klass* self,FXuint state){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<subklass*>(self)->public_drawCursor(state); \
  } \
inline FXuint klass ## _style(klass* self,FXint row,FXint beg,FXint end,FXint pos){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  return dynamic_cast<subklass*>(self)->public_style(row, beg, end, pos); \
  } \
inline void klass ## _drawBufferText(klass* self,FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h,FXint pos,FXint n,FXuint style){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<subklass*>(self)->public_drawBufferText(dc, x, y, w, h, pos, n, style); \
  } \
inline void klass ## _fillBufferRect(klass* self,FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h,FXuint style){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<subklass*>(self)->public_fillBufferRect(dc, x, y, w, h, style); \
  } \
inline void klass ## _drawTextRow(klass* self,FXDCWindow& dc,FXint line,FXint left,FXint right){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<subklass*>(self)->public_drawTextRow(dc, line, left, right); \
  } \
inline void klass ## _drawContents(klass* self,FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<subklass*>(self)->public_drawContents(dc, x, y, w, h); \
  } \
inline void klass ## _drawNumbers(klass* self,FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h){ \
  FXASSERT(self->isMemberOf(FXMETACLASS(subklass))); \
  dynamic_cast<subklass*>(self)->public_drawNumbers(dc, x, y, w, h); \
  } \
inline void klass ## _setCursorPos(klass* self,FXint pos,FXbool notify){ \
  self->klass::setCursorPos(pos,notify); \
  } \
inline FXbool klass ## _extendSelection(klass* self,FXint pos,FXTextSelectionMode mode=SELECT_CHARS,FXbool notify=FALSE){ \
  return self->klass::extendSelection(pos,mode,notify); \
  } \
inline FXbool klass ## _killSelection(klass* self,FXbool notify=FALSE){ \
  return self->klass::killSelection(notify); \
  } \
inline void klass ## _replaceText(klass* self,FXint pos,FXint m,const FXString& text,FXbool notify){ \
  self->klass::replaceText(pos,m,text.text(),text.length(),notify); \
  } \
inline void klass ## _replaceStyledText(klass* self,FXint pos,FXint m,const FXString& text,FXint style,FXbool notify){ \
  self->klass::replaceStyledText(pos,m,text.text(),text.length(),style,notify); \
  } \
inline void klass ## _appendText(klass* self,const FXString& text,FXbool notify){ \
  self->klass::appendText(text.text(),text.length(),notify); \
  } \
inline void klass ## _appendStyledText(klass* self,const FXString& text,FXint style,FXbool notify){ \
  self->klass::appendStyledText(text.text(),text.length(),style,notify); \
  } \
inline void klass ## _insertText(klass* self,FXint pos,const FXString& text,FXbool notify){ \
  self->klass::insertText(pos,text.text(),text.length(),notify); \
  } \
inline void klass ## _insertStyledText(klass* self,FXint pos,const FXString& text,FXint style,FXbool notify){ \
  self->klass::insertStyledText(pos,text.text(),text.length(),style,notify); \
  } \
inline void klass ## _removeText(klass* self,FXint pos,FXint n,FXbool notify){ \
  self->klass::removeText(pos,n,notify); \
  } \
inline void klass ## _changeStyle(klass* self,FXint pos,FXint n,FXint style){ \
  self->klass::changeStyle(pos,n,style); \
  } \
inline void klass ## _changeStyle(klass* self,FXint pos,const FXString& style){ \
  self->klass::changeStyle(pos,style.text(),style.length()); \
  } \
inline void klass ## _setText(klass* self,const FXString& text,FXbool notify){ \
  self->klass::setText(text.text(),text.length(),notify); \
  } \
inline void klass ## _setStyledText(klass* self,const FXString& text,FXint style,FXbool notify){ \
  self->klass::setStyledText(text.text(),text.length(),style,notify); \
  }


#define IMPLEMENT_FXTEXT_STUBS(cls,superklass) \
  void cls::eraseCursorOverhang(){ \
    HinCallVoidMethod(this,"eraseCursorOverhang"); \
    } \
  void cls::public_eraseCursorOverhang(){ \
    superklass::eraseCursorOverhang(); \
    } \
  void cls::drawCursor(FXuint state){ \
    HinCallVoidMethod(this,"drawCursor", state); \
    } \
  void cls::public_drawCursor(FXuint state){ \
    superklass::drawCursor(state); \
    } \
  FXuint cls::style(FXint row,FXint beg,FXint end,FXint pos){ \
    return HinCallUIntMethod(this,"style", row, beg, end, pos); \
    } \
  FXuint cls::public_style(FXint row,FXint beg,FXint end,FXint pos){ \
    return superklass::style(row, beg, end, pos); \
    } \
  void cls::drawBufferText(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h,FXint pos,FXint n,FXuint style){ \
    HinCallVoidMethod(this,"drawBufferText", dc, x, y, w, h, pos, n, style); \
    } \
  void cls::public_drawBufferText(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h,FXint pos,FXint n,FXuint style){ \
    superklass::drawBufferText(dc, x, y, w, h, pos, n, style); \
    } \
  void cls::fillBufferRect(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h,FXuint style){ \
    HinCallVoidMethod(this,"fillBufferRect", dc, x, y, w, h, style); \
    } \
  void cls::public_fillBufferRect(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h,FXuint style){ \
    superklass::fillBufferRect(dc, x, y, w, h, style); \
    } \
  void cls::drawTextRow(FXDCWindow& dc,FXint line,FXint left,FXint right){ \
    HinCallVoidMethod(this,"drawTextRow", dc, line, left, right); \
    } \
  void cls::public_drawTextRow(FXDCWindow& dc,FXint line,FXint left,FXint right){ \
    superklass::drawTextRow(dc, line, left, right); \
    } \
  void cls::drawContents(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h){ \
    HinCallVoidMethod(this,"drawContents", dc, x, y, w, h); \
    } \
  void cls::public_drawContents(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h){ \
    superklass::drawContents(dc, x, y, w, h); \
    } \
  void cls::drawNumbers(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h){ \
    HinCallVoidMethod(this,"drawNumbers", dc, x, y, w, h); \
    } \
  void cls::public_drawNumbers(FXDCWindow& dc,FXint x,FXint y,FXint w,FXint h){ \
    superklass::drawNumbers(dc, x, y, w, h); \
    } \
  void cls::setCursorPos(FXint pos,FXbool notify){ \
    HinCallVoidMethod(this,"setCursorPos",pos,notify); \
    } \
  FXbool cls::extendSelection(FXint pos,FXTextSelectionMode mode,FXbool notify){ \
    return HinCallBoolMethod(this,"extendSelection",pos,mode,notify); \
    } \
  FXbool cls::killSelection(FXbool notify){ \
    return HinCallBoolMethod(this,"killSelection",notify); \
    } \
  void cls::replaceText(FXint pos,FXint m,const FXchar *text,FXint n,FXbool notify){ \
    HinCallVoidMethod(this,"replaceText",pos,m,FXString(text,n),notify); \
    } \
  void cls::replaceText(FXint pos,FXint m,const FXString& text,FXbool notify){ \
    HinCallVoidMethod(this,"replaceText",pos,m,text,notify); \
    } \
  void cls::replaceStyledText(FXint pos,FXint m,const FXchar *text,FXint n,FXint style,FXbool notify){ \
    HinCallVoidMethod(this,"replaceStyledText",pos,m,FXString(text,n),style,notify); \
    } \
  void cls::replaceStyledText(FXint pos,FXint m,const FXString& text,FXint style,FXbool notify){ \
    HinCallVoidMethod(this,"replaceStyledText",pos,m,text,style,notify); \
    } \
  void cls::appendText(const FXchar *text,FXint n,FXbool notify){ \
    HinCallVoidMethod(this,"appendText",FXString(text,n),notify); \
    } \
  void cls::appendText(const FXString& text,FXbool notify){ \
    HinCallVoidMethod(this,"appendText",text,notify); \
    } \
  void cls::appendStyledText(const FXchar *text,FXint n,FXint style,FXbool notify){ \
    HinCallVoidMethod(this,"appendStyledText",FXString(text,n),style,notify); \
    } \
  void cls::appendStyledText(const FXString& text,FXint style,FXbool notify){ \
    HinCallVoidMethod(this,"appendStyledText",text,style,notify); \
    } \
  void cls::insertText(FXint pos,const FXchar *text,FXint n,FXbool notify){ \
    HinCallVoidMethod(this,"insertText",pos,FXString(text,n),notify); \
    } \
  void cls::insertText(FXint pos,const FXString& text,FXbool notify){ \
    HinCallVoidMethod(this,"insertText",pos,text,notify); \
    } \
  void cls::insertStyledText(FXint pos,const FXchar *text,FXint n,FXint style,FXbool notify){ \
    HinCallVoidMethod(this,"insertStyledText",pos,FXString(text,n),style,notify); \
    } \
  void cls::insertStyledText(FXint pos,const FXString& text,FXint style,FXbool notify){ \
    HinCallVoidMethod(this,"insertStyledText",pos,text,style,notify); \
    } \
  void cls::removeText(FXint pos,FXint n,FXbool notify){ \
    HinCallVoidMethod(this,"removeText",pos,n,notify); \
    } \
  void cls::changeStyle(FXint pos,FXint n,FXint style){ \
    HinCallVoidMethod(this,"changeStyle",pos,n,style); \
    } \
  void cls::changeStyle(FXint pos,const FXchar* style,FXint n){ \
    HinCallVoidMethod(this,"changeStyle",pos,FXString(style,n)); \
    } \
  void cls::changeStyle(FXint pos,const FXString& style){ \
    HinCallVoidMethod(this,"changeStyle",pos,style); \
    } \
  void cls::setText(const FXchar* text,FXint n,FXbool notify){ \
    HinCallVoidMethod(this,"setText",FXString(text,n),notify); \
    } \
  void cls::setText(const FXString& text,FXbool notify){ \
    HinCallVoidMethod(this,"setText",text,notify); \
    } \
  void cls::setStyledText(const FXchar* text,FXint n,FXint style,FXbool notify){ \
    HinCallVoidMethod(this,"setStyledText",FXString(text,n),style,notify); \
    } \
  void cls::setStyledText(const FXString& text,FXint style,FXbool notify){ \
    HinCallVoidMethod(this,"setStyledText",text,style,notify); \
    }


class HinText : public FXText {
  FXDECLARE(HinText)
protected:
  HinText(){}
#include "HinObjectVirtuals.h"
#include "HinIdVirtuals.h"
#include "HinDrawableVirtuals.h"
#include "HinWindowVirtuals.h"
#include "HinScrollAreaVirtuals.h"
#include "HinTextVirtuals.h"
public:
  /// Construct multi-line text widget
  HinText(FXComposite *p,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=3,FXint pr=3,FXint pt=2,FXint pb=2) : FXText(p,tgt,sel,opts,x,y,w,h,pl,pr,pt,pb){
    numStyles=0;
    styles=0;
    }

  // Number of styles in style array
  FXint numStyles;

  // Style array
  FXHiliteStyle *styles;


  // Mark dependencies for the GC
  static void markfunc(FXText* self);

  // Unregister objects that this text owns and is about to destroy
  static void unregisterOwnedObjects(FXText *pText);

  // Destructor
  virtual ~HinText(){
    numStyles=0;
    delete [] styles;
    styles=(FXHiliteStyle*)-1;
    HinText::unregisterOwnedObjects(this);
    HinUnregisterRubyObj(this);
    }
  };

#endif
