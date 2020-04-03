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
 * $Id: Hinamori.h 2463 2006-07-11 14:02:35Z lyle $
 ***********************************************************************/

#ifndef FXRUBY_H
#define FXRUBY_H

#ifndef NUM2SIZET
#define NUM2SIZET(s) NUM2ULONG(s)
#endif
#ifndef SIZET2NUM
#define SIZET2NUM(s) ULONG2NUM(s)
#endif

// Opaque type declaration for SWIG runtime support
struct swig_type_info;

// SWIG runtime functions we need
extern "C" {
static const char * SWIG_TypeName(const swig_type_info *ty);
static VALUE SWIG_Ruby_NewPointerObj(void *ptr, swig_type_info *type, int own);
static int FXSWIG_ConvertPtr(VALUE obj, void **ptr, swig_type_info *ty, int flags);
}

// Helper for overloaded show() functions
template <class TYPE>
VALUE showHelper(VALUE self, int argc, VALUE *argv, TYPE *p, swig_type_info *typeinfo) {
  TYPE *win;
  FXSWIG_ConvertPtr(self,(void**)&win,typeinfo,1);
  if (argc == 0) {
    win->_show();
    }
  else if (argc == 1) {
    FXuint placement = NUM2UINT(argv[0]);
    win->FXTopWindow::show(placement);
    }
  else {
    rb_raise(rb_eArgError, "wrong # of arguments");
    }
  return Qnil;
  }

// Wrapper around SWIG_Ruby_NewPointerObj()
VALUE HinNewPointerObj(void *ptr, swig_type_info *typeinfo);
VALUE HinNewPointerObjCb(void *ptr, swig_type_info *typeinfo);
bool HinIsBorrowed(void* ptr);
bool HinSetInGC(const void* ptr, bool enabled);
bool HinIsInGC(const void* ptr);

// Wrapper around SWIG_TypeQuery()
swig_type_info *HinTypeQuery(const char *name);

// Wrapper around SWIG_ConvertPtr()
void* HinConvertPtr(VALUE obj,swig_type_info* typeinfo);

// Returns an FXInputHandle for this Ruby file object
FXInputHandle HinGetReadFileHandle(VALUE obj,FXuint mode);
FXInputHandle HinGetWriteFileHandle(VALUE obj,FXuint mode);
void HinRemoveReadFileHandle(VALUE obj,FXuint mode);
void HinRemoveWriteFileHandle(VALUE obj,FXuint mode);

// Register mapping from Ruby objects to FOX objects
void HinRegisterRubyObj(VALUE rubyObj, const void* hinObj);

// Remove mapping for this FOX object and zero out any pointers
// to this (now dead) C++ object held by any Ruby object
void HinUnregisterRubyObj(const void* hinObj);

// Register an object that must be destroyed before FXApp is destroyed
void HinRegisterAppSensitiveObject(FXObject* obj);
void HinRegisterAppSensitiveObject(FXDC* dc);

// Unregister an object that must be destroyed before FXApp is destroyed
void HinUnregisterAppSensitiveObject(FXObject* obj);
void HinUnregisterAppSensitiveObject(FXDC* dc);

// Destroy all app-sensitive objects
void HinDestroyAppSensitiveObjects();

/**
 * Return the registered Ruby class instance associated with this
 * FOX object (if any). If searchBoth is false, only considers the
 * Ruby-owned objects; otherwise considers all outstanding references.
 */
VALUE HinGetRubyObj(const void *hinObj, bool searchBoth, bool in_gc_mark=false);

/**
 * Return the registered Ruby class instance associated with this
 * FOX object, or a new unregistered instance if not found.
 */
VALUE HinGetRubyObj(const void *hinObj, const char *type);
VALUE HinGetRubyObj(const void *hinObj, swig_type_info *type);
VALUE HinGetRubyObjCb(const void *hinObj, swig_type_info *type);


// Mark this object as used for the garbage collector
void HinGcMark(void *obj);

// Returns a Ruby array of floats
extern VALUE HinMakeArray(const FXfloat* values,FXint size);

// Returns a Ruby array of floats
extern VALUE HinMakeArray(const FXdouble* values,FXint size);

// Returns a Ruby array of integers
extern VALUE HinMakeArray(const FXint* values,FXint size);

// Returns a Ruby array of integers
extern VALUE HinMakeArray(const FXuint* values,FXint size);

// Returns a Ruby array of integers
extern VALUE HinMakeArray(const FXchar* dashpattern,FXuint dashlength);

// Returns a Ruby array of FXArcs
extern VALUE HinMakeArray(const FXArc* arcs,FXuint narcs);

// Returns a Ruby array of FXPoints
extern VALUE HinMakeArray(const FXPoint* points,FXuint npoints);

// Returns a Ruby array of FXRectangles
extern VALUE HinMakeArray(const FXRectangle* rectangles,FXuint nrectangles);

// Returns a Ruby array of FXSegments
extern VALUE HinMakeArray(const FXSegment* segments,FXuint nsegments);

// Returns a Ruby array of FXColor values
extern VALUE HinMakeColorArray(const FXColor* colors,FXint w,FXint h);

// Returns a number of FXColor elements in the argument
extern FXuint HinNumberOfFXColors(VALUE string_or_ary);

// Allocate a FXColor buffer and populate with data
extern FXColor *HinConvertToFXColors(VALUE string_or_ary, FXuint *opts);

extern void* HinGetExpectedData(VALUE recv,FXSelector key,VALUE data);

// Returns the name of the message handler function (or NULL)
ID HinLookupHandler_gvlcb(FXObject* recv,FXSelector key);

// Handle this message
long HinHandleMessage_gvlcb(FXObject* recv,ID func,FXObject* sender,FXSelector key,void* data);

// Convert a signal name string to its corresponding signal number
FXint HinSignalNameToNumber(const char* name);

// Fox module instance
extern VALUE mFox;

#ifdef HAVE_RUBY_ENCODING_H
// UTF-8 encoding index
extern int utf8_enc_idx;
#endif

// Convert from FOX datatypes to Ruby objects
inline VALUE to_ruby(const void* ptr){
  return Qnil; // FIXME: Used for some FXIconSource methods
  }

inline VALUE to_ruby(FXchar c){
  return INT2NUM(c);
  }

inline VALUE to_ruby(FXbool b){ // same as FXuchar
  return b ? Qtrue : Qfalse;
  }

inline VALUE to_ruby(FXshort s){
  return INT2NUM(s);
  }

inline VALUE to_ruby(FXushort u){
  return UINT2NUM(u);
  }

inline VALUE to_ruby(FXint i){
  return INT2NUM(i);
  }

inline VALUE to_ruby(FXuint u){
  return UINT2NUM(u);
  }

inline VALUE to_ruby(FXfloat f){
  return rb_float_new(f);
  }

inline VALUE to_ruby(FXdouble d){
  return rb_float_new(d);
  }

inline VALUE to_ruby(FXlong x){
  return LONG2NUM(x);
  }

inline VALUE to_ruby(FXulong x){
  return ULONG2NUM(x);
  }

#if !defined(__LP64__) && !defined(_LP64) && (_MIPS_SZLONG != 64) && (__WORDSIZE != 64)
inline VALUE to_ruby(unsigned long l){
  return ULONG2NUM(l);
  }
#endif

inline VALUE to_ruby(const FXString& s){
  VALUE str = rb_str_new(s.text(), s.length());
#ifdef HAVE_RUBY_ENCODING_H
  rb_enc_associate_index(str, utf8_enc_idx);
#endif
  return str;
  }

inline VALUE to_ruby(const FXchar* s){
  if(!s) return Qnil;
  VALUE str = rb_str_new2(s);
#ifdef HAVE_RUBY_ENCODING_H
  rb_enc_associate_index(str, utf8_enc_idx);
#endif
  return str;
  }

inline VALUE to_ruby(const FXchar* s, int length){
  VALUE str = rb_str_new(s, length);
#ifdef HAVE_RUBY_ENCODING_H
  rb_enc_associate_index(str, utf8_enc_idx);
#endif
  return str;
  }

extern VALUE to_ruby(const FXObject* obj);

inline VALUE to_ruby(const FXRangef& range){
  return HinNewPointerObj(static_cast<void*>(const_cast<FXRangef*>(&range)),HinTypeQuery("FXRangef *"));
  }

inline VALUE to_ruby(FXStream& store){
  return (VALUE) 0; // FIXME
  }

inline VALUE to_ruby(const FXPoint* point){
  return HinNewPointerObj(static_cast<void*>(const_cast<FXPoint*>(point)),HinTypeQuery("FXPoint *"));
  }

inline VALUE to_ruby(const FXSegment* segment){
  return HinNewPointerObj(static_cast<void*>(const_cast<FXSegment*>(segment)),HinTypeQuery("FXSegment *"));
  }

inline VALUE to_ruby(const FXRectangle* rect){
  return HinNewPointerObj(static_cast<void*>(const_cast<FXRectangle*>(rect)),HinTypeQuery("FXRectangle *"));
  }

inline VALUE to_ruby(const FXRectangle& rect){
  return HinNewPointerObj(static_cast<void*>(const_cast<FXRectangle*>(&rect)),HinTypeQuery("FXRectangle *"));
  }

inline VALUE to_ruby(const FXArc* arc){
  return HinNewPointerObj(static_cast<void*>(const_cast<FXArc*>(arc)),HinTypeQuery("FXArc *"));
  }

inline VALUE to_ruby(const FXRegion& region){
  return (VALUE) 0; // FIXME
  }

inline VALUE to_ruby(FXEvent* event){
  return HinGetRubyObj(reinterpret_cast<void*>(event),HinTypeQuery("FXEvent *"));
  }

inline VALUE to_ruby(FXTablePos* p){
  return SWIG_Ruby_NewPointerObj(reinterpret_cast<void*>(p),HinTypeQuery("FXTablePos *"),0);
  }

inline VALUE to_ruby(FXTextChange* p){
  return SWIG_Ruby_NewPointerObj(reinterpret_cast<void*>(p),HinTypeQuery("FXTextChange *"),0);
  }

inline VALUE to_ruby(FXTableRange* r){
  return SWIG_Ruby_NewPointerObj(reinterpret_cast<void*>(r),HinTypeQuery("FXTableRange *"),0);
  }

inline VALUE to_ruby(FXFontDesc* fontdesc){
  return HinNewPointerObj(reinterpret_cast<void*>(fontdesc),HinTypeQuery("FXFontDesc *"));
  }

inline VALUE to_ruby(const FXFontDesc& fontdesc){
  return HinNewPointerObj(reinterpret_cast<void*>(const_cast<FXFontDesc*>(&fontdesc)),HinTypeQuery("FXFontDesc *"));
  }

inline VALUE to_ruby(FXDC& dc){
  return HinGetRubyObj(reinterpret_cast<void*>(&dc),HinTypeQuery("FXDC *"));
  }




extern VALUE to_ruby_cb(const FXObject* obj);

inline VALUE to_ruby_cb(const FXRangef& range){
  return HinNewPointerObjCb(static_cast<void*>(const_cast<FXRangef*>(&range)), HinTypeQuery("FXRangef *"));
}

inline VALUE to_ruby_cb(FXStream& store){
  return (VALUE) 0; // FIXME
}

inline VALUE to_ruby_cb(const FXPoint* point){
  return HinNewPointerObjCb(static_cast<void*>(const_cast<FXPoint*>(point)), HinTypeQuery("FXPoint *"));
}

inline VALUE to_ruby_cb(const FXSegment* segment){
  return HinNewPointerObjCb(static_cast<void*>(const_cast<FXSegment*>(segment)), HinTypeQuery("FXSegment *"));
}

inline VALUE to_ruby_cb(const FXRectangle* rect){
  return HinNewPointerObjCb(static_cast<void*>(const_cast<FXRectangle*>(rect)), HinTypeQuery("FXRectangle *"));
}

inline VALUE to_ruby_cb(const FXRectangle& rect){
  return HinNewPointerObjCb(static_cast<void*>(const_cast<FXRectangle*>(&rect)), HinTypeQuery("FXRectangle *"));
}

inline VALUE to_ruby_cb(const FXArc* arc){
  return HinNewPointerObjCb(static_cast<void*>(const_cast<FXArc*>(arc)), HinTypeQuery("FXArc *"));
}

inline VALUE to_ruby_cb(FXEvent* event){
  return HinGetRubyObjCb(reinterpret_cast<void*>(event), HinTypeQuery("FXEvent *"));
}

inline VALUE to_ruby_cb(FXFontDesc* fontdesc){
  return HinNewPointerObjCb(reinterpret_cast<void*>(fontdesc), HinTypeQuery("FXFontDesc *"));
}

inline VALUE to_ruby_cb(const FXFontDesc& fontdesc){
  return HinNewPointerObjCb(reinterpret_cast<void*>(const_cast<FXFontDesc*>(&fontdesc)), HinTypeQuery("FXFontDesc *"));
}

inline VALUE to_ruby_cb(FXDC& dc){
  return HinGetRubyObjCb(reinterpret_cast<void*>(&dc), HinTypeQuery("FXDC *"));
}
inline VALUE to_ruby_cb(FXDCWindow& dc){
  return HinGetRubyObjCb(reinterpret_cast<void*>(&dc), HinTypeQuery("FXDCWindow *"));
}

template<class TYPE>
VALUE to_ruby_cb(TYPE obj){
  return to_ruby(obj);
}


/**
 * Remember: FXID is typedef'd as an unsigned int on non-Windows platforms,
 * but as a void * on Win32.
 */
inline VALUE fxid_to_int(FXID id){
#ifndef WIN32
  return UINT2NUM(static_cast<unsigned int>(id));
#else
  return SIZET2NUM(reinterpret_cast<size_t>(id));
#endif
  }

/**
 * Remember: FXID is typedef'd as an unsigned int on non-Windows platforms,
 * but as a void * on Win32.
 */
inline FXID int_to_fxid(VALUE value){
#ifndef WIN32
  return static_cast<FXID>(NUM2UINT(value));
#else
  return reinterpret_cast<FXID>(NUM2SIZET(value));
#endif
  }

// Returns the beginning and ending values (inclusive) for a Range object
void HinRange2LoHi(VALUE range,FXint& lo,FXint& hi);
void HinRange2LoHi(VALUE range,FXdouble& lo,FXdouble& hi);

// Call function with "void" return value
void HinCallVoidMethod_gvlcb(FXObject* recv,const char *func);

void HinCallVoidMethod_gvlcb(FXDC* recv,const char *func);

/* One argument */
template<class TYPE>
void HinCallVoidMethod_gvlcb(FXObject* recv,const char *func, TYPE& arg){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  FXASSERT(!HinIsInGC(recv));
  rb_funcall(obj,rb_intern(func),1,to_ruby_cb(arg));
  }

template<class TYPE>
void HinCallVoidMethod_gvlcb(FXDC* recv,const char *func,TYPE arg){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),1,to_ruby_cb(arg));
  }

template<class TYPE>
void HinCallVoidMethod_gvlcb(const FXObject* recv, const char *func, TYPE& arg){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  FXASSERT(!HinIsInGC(recv));
  rb_funcall(obj,rb_intern(func),1,to_ruby_cb(arg));
  }

/* Two arguments */
template<class TYPE1, class TYPE2>
void HinCallVoidMethod_gvlcb(FXObject* recv,const char *func,TYPE1 arg1,TYPE2 arg2){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),2,to_ruby_cb(arg1),to_ruby_cb(arg2));
  }

template<class TYPE1, class TYPE2>
void HinCallVoidMethod_gvlcb(FXDC* recv,const char *func,TYPE1 arg1,TYPE2 arg2){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),2,to_ruby_cb(arg1),to_ruby_cb(arg2));
  }

template<class TYPE>
void HinCallVoidArrayMethod(FXDC* recv,const char *func,TYPE objs,FXuint num){
  VALUE obj=HinGetRubyObj(recv,false);
  VALUE array=HinMakeArray(objs,num);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),1,array);
}

FXTreeItem* HinCallTreeItemMethod_gvlcb(const FXTreeList* recv,const char *func,FXint x,FXint y);
FXFoldingItem* HinCallFoldingItemMethod_gvlcb(const FXFoldingList* recv,const char *func,FXint x,FXint y);

/* Three arguments */
template<class TYPE1, class TYPE2, class TYPE3>
void HinCallVoidMethod_gvlcb(FXObject* recv,const char *func,TYPE1 arg1,TYPE2 arg2,TYPE3 arg3){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),3,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3));
  }

template<class TYPE1, class TYPE2, class TYPE3>
void HinCallVoidMethod_gvlcb(FXDC* recv,const char *func,TYPE1 arg1,TYPE2 arg2,TYPE3 arg3){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),3,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3));
  }

/* Four arguments */
template<class TYPE1, class TYPE2, class TYPE3, class TYPE4>
void HinCallVoidMethod_gvlcb(FXObject* recv,const char *func, TYPE1& arg1, TYPE2 arg2, TYPE3 arg3, TYPE4 arg4){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),4,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4));
  }

template<class TYPE1, class TYPE2, class TYPE3, class TYPE4>
void HinCallVoidMethod_gvlcb(FXDC* recv,const char *func,TYPE1 arg1,TYPE2 arg2,TYPE3 arg3,TYPE4 arg4){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),4,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4));
  }

/* Five arguments */
template<class TYPE1, class TYPE2, class TYPE3, class TYPE4, class TYPE5>
void HinCallVoidMethod_gvlcb(FXObject* recv,const char *func,TYPE1& arg1,TYPE2 arg2,TYPE3 arg3,TYPE4 arg4,TYPE5 arg5){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),5,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4),to_ruby_cb(arg5));
  }

template<class TYPE1, class TYPE2, class TYPE3, class TYPE4, class TYPE5>
void HinCallVoidMethod_gvlcb(FXDC* recv, const char *func, TYPE1 arg1, TYPE2 arg2, TYPE3 arg3, TYPE4 arg4, TYPE5 arg5){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),5,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4),to_ruby_cb(arg5));
  }

/* Six arguments */
template<class TYPE1, class TYPE2, class TYPE3, class TYPE4, class TYPE5, class TYPE6>
void HinCallVoidMethod_gvlcb(const FXObject* recv, const char *func, TYPE1& arg1, TYPE2& arg2, TYPE3 arg3, TYPE4 arg4, TYPE5 arg5, TYPE6 arg6){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),6,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4),to_ruby_cb(arg5),to_ruby_cb(arg6));
  }

template<class TYPE1, class TYPE2, class TYPE3, class TYPE4, class TYPE5, class TYPE6>
void HinCallVoidMethod_gvlcb(FXDC* recv, const char *func, TYPE1 arg1, TYPE2 arg2, TYPE3 arg3, TYPE4 arg4, TYPE5 arg5, TYPE6 arg6){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),6,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4),to_ruby_cb(arg5),to_ruby_cb(arg6));
  }

/* Seven arguments */
template<class TYPE1, class TYPE2, class TYPE3, class TYPE4, class TYPE5, class TYPE6, class TYPE7>
void HinCallVoidMethod_gvlcb(FXDC* recv, const char *func, TYPE1 arg1, TYPE2 arg2, TYPE3 arg3, TYPE4 arg4, TYPE5 arg5, TYPE6 arg6, TYPE7 arg7){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),7,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4),to_ruby_cb(arg5),to_ruby_cb(arg6),to_ruby_cb(arg7));
  }

template<class TYPE1, class TYPE2, class TYPE3, class TYPE4, class TYPE5, class TYPE6, class TYPE7, class TYPE8>
void HinCallVoidMethod_gvlcb(FXObject* recv, const char *func, TYPE1& arg1, TYPE2 arg2, TYPE3 arg3, TYPE4 arg4, TYPE5 arg5, TYPE6 arg6, TYPE7 arg7, TYPE8 arg8){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),8,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4),to_ruby_cb(arg5),to_ruby_cb(arg6),to_ruby_cb(arg7), to_ruby_cb(arg8));
  }

/* Nine arguments */
template<class TYPE1, class TYPE2, class TYPE3, class TYPE4, class TYPE5, class TYPE6, class TYPE7, class TYPE8, class TYPE9>
void HinCallVoidMethod_gvlcb(FXDC* recv, const char *func, TYPE1 arg1, TYPE2 arg2, TYPE3 arg3, TYPE4 arg4, TYPE5 arg5, TYPE6 arg6, TYPE7 arg7, TYPE8 arg8, TYPE9 arg9){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),9,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4),to_ruby_cb(arg5),to_ruby_cb(arg6),to_ruby_cb(arg7), to_ruby_cb(arg8), to_ruby_cb(arg9));
  }

/* Eleven arguments (!) */
template<class TYPE1,class TYPE2,class TYPE3,class TYPE4,class TYPE5,class TYPE6,class TYPE7,class TYPE8,class TYPE9,class TYPE10,class TYPE11>
void HinCallVoidMethod_gvlcb(FXObject* recv,const char *func,TYPE1& arg1,TYPE2 arg2,TYPE3 arg3,TYPE4 arg4,TYPE5 arg5,TYPE6 arg6,TYPE7 arg7,TYPE8 arg8,TYPE9 arg9,TYPE10 arg10,TYPE11 arg11){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  rb_funcall(obj,rb_intern(func),11,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4),to_ruby_cb(arg5),to_ruby_cb(arg6),to_ruby_cb(arg7),to_ruby_cb(arg8),to_ruby_cb(arg9),to_ruby_cb(arg10),to_ruby_cb(arg11));
  }

// Call function with "FXbool" return value
inline bool HinCallBoolMethod_gvlcb(FXStream* recv,const char *func){
  VALUE v=rb_funcall(HinGetRubyObj(recv,false),rb_intern(func),0);
  return (v==Qtrue);
  }

template<class TYPE1>
bool HinCallBoolMethod_gvlcb(FXStream* recv,const char *func,TYPE1 arg){
  VALUE v=rb_funcall(HinGetRubyObj(recv,false),rb_intern(func),1,to_ruby_cb(arg));
  return (v==Qtrue);
  }

template<class TYPE1,class TYPE2>
bool HinCallBoolMethod_gvlcb(FXStream* recv,const char *func,TYPE1 arg1,TYPE2 arg2){
  VALUE v=rb_funcall(HinGetRubyObj(recv,false),rb_intern(func),2,to_ruby_cb(arg1),to_ruby_cb(arg2));
  return (v==Qtrue);
  }

bool HinCallBoolMethod_gvlcb(const FXObject* recv,const char *func);

template<class TYPE>
bool HinCallBoolMethod_gvlcb(FXObject* recv, const char *func, TYPE& arg){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE v=rb_funcall(obj,rb_intern(func),1,to_ruby_cb(arg));
  return (v==Qtrue);
  }

template<class TYPE>
bool HinCallBoolMethod_gvlcb(const FXObject* recv,const char *func,TYPE& arg){
  VALUE v=rb_funcall(HinGetRubyObj(recv,false),rb_intern(func),1,to_ruby_cb(arg));
  return (v==Qtrue);
  }

template<class TYPE1, class TYPE2>
bool HinCallBoolMethod_gvlcb(const FXObject* recv, const char *func, TYPE1 arg1, TYPE2 arg2){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE v=rb_funcall(obj,rb_intern(func),2,to_ruby_cb(arg1),to_ruby_cb(arg2));
  return (v==Qtrue);
  }

template<class TYPE1, class TYPE2, class TYPE3>
bool HinCallBoolMethod_gvlcb(const FXObject* recv, const char *func, TYPE1 arg1, TYPE2 arg2, TYPE3 arg3){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE v=rb_funcall(obj,rb_intern(func),3,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3));
  return (v==Qtrue);
  }

template<class TYPE1, class TYPE2, class TYPE3, class TYPE4, class TYPE5>
bool HinCallBoolMethod_gvlcb(const FXObject* recv, const char *func, TYPE1 arg1, TYPE2 arg2, TYPE3 arg3, TYPE4 arg4, TYPE5 arg5){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE v=rb_funcall(obj,rb_intern(func),5,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4),to_ruby_cb(arg5));
  return (v==Qtrue);
  }

// Call function with "FXint" return value
FXint HinCallIntMethod_gvlcb(const FXObject* recv,const char *func);

template<class TYPE>
FXint HinCallIntMethod_gvlcb(FXObject* recv, const char *func, TYPE arg){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE v=rb_funcall(obj,rb_intern(func),1,to_ruby_cb(arg));
  return static_cast<FXint>(NUM2INT(v));
  }

template<class TYPE>
FXint HinCallIntMethod_gvlcb(const FXObject* recv, const char *func, TYPE arg){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE v=rb_funcall(obj,rb_intern(func),1,to_ruby_cb(arg));
  return static_cast<FXint>(NUM2INT(v));
  }

template<class TYPE1, class TYPE2>
FXint HinCallIntMethod_gvlcb(const FXObject* recv, const char *func, TYPE1 arg1, TYPE2 arg2){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,rb_intern(func),2,to_ruby_cb(arg1),to_ruby_cb(arg2));
  return static_cast<FXint>(NUM2INT(result));
  }

template<class TYPE1, class TYPE2, class TYPE3, class TYPE4, class TYPE5>
FXint HinCallIntMethod_gvlcb(const FXObject* recv, const char *func, TYPE1 arg1, TYPE2 arg2, TYPE3 arg3, TYPE4 arg4, TYPE5 arg5){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,rb_intern(func),5,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4),to_ruby_cb(arg5));
  return static_cast<FXint>(NUM2INT(result));
  }

// Call function with "long" return value
template<class TYPE1, class TYPE2, class TYPE3>
long HinCallLongMethod_gvlcb(FXObject* recv, const char *func, TYPE1 arg1, TYPE2 arg2, TYPE3 arg3){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE v=rb_funcall(obj,rb_intern(func),3,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3));
  return static_cast<long>(NUM2LONG(v));
  }

// Call functions with "FXuint" return value
template<class TYPE>
FXuint HinCallUIntMethod_gvlcb(FXObject* recv, const char *func, TYPE arg){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE v=rb_funcall(obj,rb_intern(func),1,to_ruby_cb(arg));
  return static_cast<FXuint>(NUM2UINT(v));
  }

template<class TYPE1, class TYPE2, class TYPE3, class TYPE4>
FXuint HinCallUIntMethod_gvlcb(FXObject* recv, const char *func, TYPE1 arg1, TYPE2 arg2, TYPE3 arg3, TYPE4 arg4){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE v=rb_funcall(obj,rb_intern(func),4,to_ruby_cb(arg1),to_ruby_cb(arg2),to_ruby_cb(arg3),to_ruby_cb(arg4));
  return static_cast<FXuint>(NUM2UINT(v));
  }

// Call functions with FXString return value
FXString HinCallStringMethod_gvlcb(const FXObject* recv, const char *func);

// Call functions with const FXchar* return value
const FXchar* HinCallCStringMethod_gvlcb(const FXObject* recv, const char *func, const FXchar*, const FXchar*);
const FXchar* HinCallCStringMethod_gvlcb(const FXObject* recv, const char *func, const FXchar*, const FXchar*, const FXchar*);

// Call functions with "FXGLObject*" return value
FXGLObject* HinCallGLObjectMethod_gvlcb(FXGLObject* recv,const char *func);
FXGLObject* HinCallGLObjectMethod_gvlcb(FXGLObject* recv,const char *func,FXuint* path,FXint n);
FXGLObject* HinCallGLObjectMethod_gvlcb(FXGLViewer* recv,const char *func,FXint x,FXint y);

// Call functions with "FXGLObject**" return value
FXGLObject** HinCallGLObjectArrayMethod_gvlcb(FXGLViewer* recv,const char *func,FXint x,FXint y,FXint w,FXint h);

// Call functions with "FXTreeItem*" return value
FXTableItem* HinCallTableItemMethod_gvlcb(FXTable* recv,const char *func,const FXString& text,FXIcon* icon,void* ptr);

// Call functions with "FXTreeItem*" return value
FXTableItem* HinCallTableItemMethod_gvlcb(FXTable* recv,const char *func,FXint,FXint,FXbool);

// Call functions with "FXFileAssoc*" return value
FXFileAssoc* HinCallFileAssocMethod_gvlcb(const FXFileDict* recv,const char *func,const FXchar* pathname);

// Call functions with "FXIcon*" return value
FXIcon* HinCallIconMethod_gvlcb(const FXTableItem* recv,const char *func);

template<class TYPE1, class TYPE2>
FXIcon* HinCallIconMethod_gvlcb(const FXIconSource *recv,const char *func,TYPE1& arg1,const TYPE2& arg2){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,rb_intern(func),2,to_ruby(arg1),to_ruby(arg2));
  return NIL_P(result) ? 0 : reinterpret_cast<FXIcon*>(DATA_PTR(result));
  }

template<class TYPE1, class TYPE2, class TYPE3, class TYPE4>
FXIcon* HinCallIconMethod_gvlcb(const FXIconSource *recv,const char *func,TYPE1& arg1,TYPE2 arg2,TYPE3 arg3,const TYPE4& arg4){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,rb_intern(func),4,to_ruby(arg1),to_ruby(arg2),to_ruby(arg3),to_ruby(arg4));
  return NIL_P(result) ? 0 : reinterpret_cast<FXIcon*>(DATA_PTR(result));
  }

// Call functions with FXImage* return value
template<class TYPE1, class TYPE2>
FXImage* HinCallImageMethod_gvlcb(const FXIconSource *recv,const char *func,TYPE1& arg1,const TYPE2& arg2){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,rb_intern(func),2,to_ruby(arg1),to_ruby(arg2));
  return NIL_P(result) ? 0 : reinterpret_cast<FXImage*>(DATA_PTR(result));
  }

template<class TYPE1, class TYPE2, class TYPE3, class TYPE4>
FXImage* HinCallImageMethod_gvlcb(const FXIconSource *recv,const char *func,TYPE1& arg1,TYPE2 arg2,TYPE3 arg3,const TYPE4& arg4){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE result=rb_funcall(obj,rb_intern(func),4,to_ruby(arg1),to_ruby(arg2),to_ruby(arg3),to_ruby(arg4));
  return NIL_P(result) ? 0 : reinterpret_cast<FXImage*>(DATA_PTR(result));
  }

// Call functions with "FXWindow*" return value
FXWindow* HinCallWindowMethod_gvlcb(const FXTableItem* recv,const char *func,FXTable* table);

// Call functions with "FXColor" return value
template<class TYPE1, class TYPE2>
FXColor HinCallColorMethod_gvlcb(FXDC* recv, const char *func, TYPE1 arg1, TYPE2 arg2){
  VALUE obj=HinGetRubyObj(recv,false);
  FXASSERT(!NIL_P(obj));
  VALUE v=rb_funcall(obj,rb_intern(func),2,to_ruby(arg1),to_ruby(arg2));
  return static_cast<FXColor>(NUM2UINT(v));
  }

// Call functions with "FXRangef" return value
FXRangef HinCallRangeMethod_gvlcb(FXObject* recv,const char *func);

// Call functions with FXwchar return value
FXwchar HinCallWCharMethod_gvlcb(const FXObject* recv,const char *func);

void HinCallSetDashes_gvlcb(FXDC* recv,const char *func,FXuint dashoffset,const FXchar *dashpattern,FXuint dashlength);

void HinCallDCDrawMethod_gvlcb(FXDC* recv, const char * func, FXint x,FXint y,const FXString& string);
void HinCallDCDrawMethod_gvlcb(FXDC* recv, const char * func, FXint x,FXint y,const FXchar* string,FXuint length);

/**
 * Macro to set up class implementation.
 * This is a modified version of the standard FOX macro FXIMPLEMENT();
 * this version's implementation of the virtual handle() function
 * first checks the Ruby class instance's message map to see if it
 * can handle the incoming message. If not, the regular C++ message
 * mapping takes over as in standard FOX applications.
 */

#define HinIMPLEMENT(classname,baseclassname,mapping,nmappings) \
  FXObject* classname::manufacture(){return new classname;} \
  const FX::FXMetaClass classname::metaClass(#classname,classname::manufacture,&baseclassname::metaClass,mapping,nmappings,sizeof(classname::FXMapEntry)); \
  long classname::handle(FXObject* sender,FXSelector key,void* ptr){ \
    ID func=HinLookupHandler(this,key); \
    if(func!=0){ \
      return HinHandleMessage(this,func,sender,key,ptr); \
      } \
    else{ \
      const FXMapEntry* me=reinterpret_cast<const FXMapEntry*>(metaClass.search(key)); \
      return me ? (this->* me->func)(sender,key,ptr) : baseclassname::handle(sender,key,ptr); \
      } \
    }


#define SORTFUNC(list, item) \
  FXint list##_sortFunc_gvlcb(const item* a,const item* b);

SORTFUNC( HinComboBox, FXListItem )
SORTFUNC( HinFoldingList, FXFoldingItem )
SORTFUNC( HinIconList, FXIconItem )
SORTFUNC( HinList, FXListItem )
SORTFUNC( HinListBox, FXListItem )
SORTFUNC( HinTreeList, FXTreeItem )

#undef SORTFUNC

// Hinamori classes
#include "HinStream.h"
#include "HinObject.h"
#include "HinDelegator.h"
#include "HinDict.h"
#include "HinStringDict.h"
#include "HinAccelTable.h"
#include "HinRecentFiles.h"
#include "HinApp.h"
#include "HinId.h"
#include "HinVisual.h"
#include "HinFont.h"
#include "HinCursor.h"
#include "HinCURCursor.h"
#include "HinGIFCursor.h"
#include "HinDrawable.h"
#include "HinBitmap.h"
#include "FXMemoryBuffer.h"
#include "HinImage.h"
#include "HinBMPImage.h"
#include "HinGIFImage.h"
#include "HinICOImage.h"
#include "HinJPGImage.h"
#include "HinPCXImage.h"
#include "HinPNGImage.h"
#include "HinPPMImage.h"
#include "HinRGBImage.h"
#include "HinTGAImage.h"
#include "HinTIFImage.h"
#include "HinXBMImage.h"
#include "HinXPMImage.h"
#include "HinIcon.h"
#include "HinBMPIcon.h"
#include "HinGIFIcon.h"
#include "HinICOIcon.h"
#include "HinJPGIcon.h"
#include "HinPCXIcon.h"
#include "HinPNGIcon.h"
#include "HinPPMIcon.h"
#include "HinRGBIcon.h"
#include "HinTGAIcon.h"
#include "HinTIFIcon.h"
#include "HinXBMIcon.h"
#include "HinXPMIcon.h"
#include "HinDC.h"
#include "HinDCWindow.h"
#include "HinDCPrint.h"
#include "HinFileDict.h"
#include "HinWindow.h"
#include "HinFrame.h"
#include "HinKnob.h"
#include "Hin7Segment.h"
#include "HinDockHandler.h"
#include "HinDockTitle.h"
#include "HinSeparator.h"
#include "HinLabel.h"
#include "HinDial.h"
#include "HinColorBar.h"
#include "HinColorRing.h"
#include "HinColorWell.h"
#include "HinColorWheel.h"
#include "HinTextField.h"
#include "HinButton.h"
#include "HinPicker.h"
#include "HinToggleButton.h"
#include "HinTriStateButton.h"
#include "HinCheckButton.h"
#include "HinRadioButton.h"
#include "HinArrowButton.h"
#include "HinMenuButton.h"
#include "HinComposite.h"
#include "HinPacker.h"
#include "HinDockBar.h"
#include "HinDockSite.h"
#include "HinSpring.h"
#include "HinHorizontalFrame.h"
#include "HinVerticalFrame.h"
#include "HinMatrix.h"
#include "HinSpinner.h"
#include "HinRealSpinner.h"
#include "HinRootWindow.h"
#include "HinCanvas.h"
#include "HinGroupBox.h"
#include "HinShell.h"
#include "HinToolTip.h"
#include "HinPopup.h"
#include "HinTopWindow.h"
#include "HinSplashWindow.h"
#include "HinDialogBox.h"
#include "HinMainWindow.h"
#include "HinMenuPane.h"
#include "HinScrollPane.h"
#include "HinMenuCaption.h"
#include "HinMenuSeparator.h"
#include "HinMenuTitle.h"
#include "HinMenuCascade.h"
#include "HinMenuCommand.h"
#include "HinMenuCheck.h"
#include "HinMenuRadio.h"
#include "HinToolBar.h"
#include "HinMenuBar.h"
#include "HinOptionMenu.h"
#include "HinSwitcher.h"
#include "HinTabBar.h"
#include "HinTabBook.h"
#include "HinTabItem.h"
#include "HinScrollBar.h"
#include "HinScrollArea.h"
#include "HinScrollWindow.h"
#include "HinList.h"
#include "HinColorList.h"
#include "HinComboBox.h"
#include "HinListBox.h"
#include "HinFoldingList.h"
#include "HinTreeList.h"
#include "HinTreeListBox.h"
// #include "HinBitmapView.h"
#include "HinImageView.h"
#include "HinTable.h"
#include "HinDragCorner.h"
#include "HinStatusBar.h"
#include "HinStatusLine.h"
#include "HinMessageBox.h"
#include "HinDirList.h"
#include "HinRealSlider.h"
#include "HinSlider.h"
#include "HinSplitter.h"
#include "Hin4Splitter.h"
#include "HinHeader.h"
#include "HinShutter.h"
#include "HinIconList.h"
#include "HinIconSource.h"
#include "HinFileList.h"
#include "HinDirBox.h"
#include "HinDriveBox.h"
#include "HinDirSelector.h"
#include "HinDirDialog.h"
#include "HinFileSelector.h"
#include "HinFileDialog.h"
#include "HinColorSelector.h"
#include "HinColorDialog.h"
#include "HinFontSelector.h"
#include "HinFontDialog.h"
#include "HinText.h"
#include "HinDataTarget.h"
#include "HinProgressBar.h"
#include "HinSearchDialog.h"
#include "HinReplaceDialog.h"
#include "HinInputDialog.h"
#include "HinProgressDialog.h"
#include "HinChoiceBox.h"
#include "HinMDIButton.h"
#include "HinMDIClient.h"
#include "HinMDIChild.h"
#include "HinDocument.h"
#include "HinToolBarGrip.h"
#include "HinToolBarShell.h"
#include "HinToolBarTab.h"
#include "HinPrintDialog.h"
#include "HinDebugTarget.h"
#include "HinGradientBar.h"
#include "HinBitmapFrame.h"
#include "HinImageFrame.h"
#include "HinRuler.h"
#include "HinRulerView.h"
#include "HinWizard.h"
#ifdef WITH_FXSCINTILLA
#include "HinScintilla.h"
#endif
#include "HinSettings.h"
#include "HinRegistry.h"
#include "HinTranslator.h"

// OpenGL support
#include "HinGLVisual.h"
#include "HinGLContext.h"
#include "HinGLCanvas.h"
#include "HinGLViewer.h"
#include "HinGLObject.h"
#include "HinGLShape.h"

// Inlined implementations of stubs
#include "inlinestubs.h"
// FXRb -> RH [Files] (RH = [R]en Is Studio of [H]inamori )
#endif

