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
 * $Id: HinGLViewer.cpp 2190 2005-08-24 07:58:47Z lyle $
 ***********************************************************************/

#include "HinCommon.h"

// Process picks
FXGLObject* HinGLViewer::processHits(FXuint *pickbuffer,FXint nhits){
  FXuint d1,d2,i,n,zmin,zmax,sel=0,nnames=0;
  if(0<=nhits){
    for(i=0,zmin=zmax=4294967295U; nhits>0; i+=n+3,nhits--){
      n=pickbuffer[i];
      d1=pickbuffer[1+i];
      d2=pickbuffer[2+i];
      if(d1<zmin || (d1==zmin && d2<=zmax)){
        zmin=d1;
        zmax=d2;
        sel=i;
	nnames=n;
        }
      }
    FXASSERT(scene->isMemberOf(FXMETACLASS(HinGLObject)) || scene->isMemberOf(FXMETACLASS(HinGLShape)));
    if(scene->isMemberOf(FXMETACLASS(HinGLObject))){
      HinGLObject* obj=dynamic_cast<HinGLObject*>(scene);
      FXASSERT(obj!=0);
      return obj->identify(&pickbuffer[4+sel],nnames-1);
      }
    else{
      HinGLShape* shape=dynamic_cast<HinGLShape*>(scene);
      FXASSERT(shape!=0);
      return shape->identify(&pickbuffer[4+sel],nnames-1);
      }
    }
  return NULL;
  }


// Build NULL-terminated list of ALL picked objects overlapping rectangle
FXGLObject** HinGLViewer::_select(FXint x,FXint y,FXint w,FXint h){
  FXGLObject *obj,**objects=NULL;
  FXint nhits,i,j;
  FXuint *hits;
  FXint nnames;
  if(scene && maxhits){
    if(selectHits(hits,nhits,x,y,w,h)){     // FIXME leak
      FXMALLOC(&objects,FXGLObject*,nhits+1);
      FXASSERT(scene->isMemberOf(FXMETACLASS(HinGLObject)) || scene->isMemberOf(FXMETACLASS(HinGLShape)));
      if(scene->isMemberOf(FXMETACLASS(HinGLObject))){
        for(i=j=0; nhits>0; i+=hits[i]+3,nhits--){
          nnames=hits[i];
          obj=dynamic_cast<HinGLObject*>(scene)->identify(&hits[4+i],nnames-1);
          if(obj!=NULL) objects[j++]=obj;
          }
        }
      else{
        for(i=j=0; nhits>0; i+=hits[i]+3,nhits--){
          nnames=hits[i];
          obj=dynamic_cast<HinGLShape*>(scene)->identify(&hits[4+i],nnames-1);
          if(obj!=NULL) objects[j++]=obj;
          }
        }
      objects[j]=NULL;
      FXFREE(&hits);
      }
    }
  return objects;
  }
