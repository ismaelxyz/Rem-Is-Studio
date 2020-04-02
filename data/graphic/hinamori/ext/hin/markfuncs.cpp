/***********************************************************************
 * $Id: markfuncs.cpp 2928 2008-12-29 19:16:57Z lyle $
 ***********************************************************************/

#include "HinCommon.h"

#ifdef MARK
#undef MARK
#endif
#define MARK(p) rb_gc_mark(reinterpret_cast<VALUE>((p)))


template<class BASECLASS,class SUBCLASS>
static void delete_if_not_owned(BASECLASS* self,SUBCLASS*){
  if(self!=0){
    if(!HinIsBorrowed(self)){
      if(self->isMemberOf(FXMETACLASS(SUBCLASS))){
        if(!dynamic_cast<SUBCLASS*>(self)->owned){
          delete self; // also unregisters it
          }
        }
      }
    HinUnregisterRubyObj(self);
    }
  }


template<class BASECLASS,class SUBCLASS>
static void delete_if_not_owned_by_app(BASECLASS* self,SUBCLASS*){
  if(self!=0){
    if(!HinIsBorrowed(self)){
      if(self->isMemberOf(FXMETACLASS(SUBCLASS))){
        if(!dynamic_cast<SUBCLASS*>(self)->ownedByApp){
          delete self; // also unregisters it
          }
        }
      }
    HinUnregisterRubyObj(self);
    }
  }


// FIXME: How to get to the target objects stored in the accelerator
// table? This is currently private (not protected) data for the class.
// See workaround in lib/hin16/accel_table.rb.
void HinAccelTable::markfunc(FXAccelTable* accelTable){
  HinObject::markfunc(accelTable);
  }


// Mark dependencies for the GC
void HinObject::markfunc(FXObject* obj){
  FXTRACE((100,"%s::markfunc(%p)\n",obj?obj->getClassName():"HinObject",obj));
  }

static void HinSetInGCParentsRecursive(FXWindow *window, bool enabled){
  HinSetInGC( window, true );
  if(window->getParent()) HinSetInGCParentsRecursive( window->getParent(), enabled );
  }

static void HinSetInGCChildrenRecursive(FXWindow *window, bool enabled){
  HinSetInGC( window, true );
  for(FXWindow* child=window->getFirst(); child; child=child->getNext()){
    HinSetInGCChildrenRecursive( child, enabled );
    }
  }


void HinObject::freefunc(FXObject* self){
  if(self!=0){
    // Unregister, but don't destroy, borrowed references
    if(HinIsBorrowed(self)){
      HinUnregisterRubyObj(self);
      return;
      }

    const FXchar* classname=self->getClassName();
    FXASSERT(classname!=0);
    FXASSERT(strlen(classname)>3);
    if(classname[0]=='F' && classname[1]=='X' && classname[2]=='R' && classname[3]=='b'){
      // FXWindow destructor calls recalc() and changeFocus() of it's parent window.
      // Since these methods are routed back to Ruby code, but calling Ruby code from
      // GC isn't a good idea, we mark the parent window as "in_gc", so that it will
      // ignore recalc() and changeFocus() calls completely.
      // The parent window should also be scheduled to be free'd. In the other case,
      // the child window would have been marked as used.
      if(self->isMemberOf(FXMETACLASS(FXWindow))){
        FXWindow *window = dynamic_cast<FXWindow*>(self);
        HinSetInGCParentsRecursive( window, true );
        HinSetInGCChildrenRecursive( window, true );
        }
      delete self;
      }
    else{
      HinUnregisterRubyObj(self);
      }
    }
  }

void HinIconSource::markfunc(FXIconSource* iconSource){
  HinObject::markfunc(iconSource);
  }

void HinTranslator::markfunc(FXTranslator* translator){
  HinObject::markfunc(translator);
  if(translator){
    HinGcMark(translator->FXTranslator::getApp());
    HinGcMark(translator->FXTranslator::getTextCodec());
    }
  }

void HinBMPIcon::markfunc(FXBMPIcon *icon){
  HinIcon::markfunc(icon);
  }


void HinIcon::markfunc(FXIcon* icon){
  HinImage::markfunc(icon);
  }


void HinImage::markfunc(FXImage* image){
  HinDrawable::markfunc(image);
  }


void HinBMPImage::markfunc(FXBMPImage* image){
  HinImage::markfunc(image);
  }


void HinBitmap::markfunc(FXBitmap* bitmap){
  HinDrawable::markfunc(bitmap);
  }


void HinButton::markfunc(FXButton* btn){
  HinLabel::markfunc(btn);
  }


void HinKnob::markfunc(FXKnob* self){
  HinFrame::markfunc(self);
  }


void HinLabel::markfunc(FXLabel* self){
  HinFrame::markfunc(self);
  if(self){
    HinGcMark(self->FXLabel::getFont());
    HinGcMark(self->FXLabel::getIcon());
    }
  }


void HinFrame::markfunc(FXFrame* frame){
  HinWindow::markfunc(frame);
  }

void Hin7Segment::markfunc(FX7Segment* seg){
  HinFrame::markfunc(seg);
  }

void HinDockHandler::markfunc(FXDockHandler *dockhandler){
  HinFrame::markfunc(dockhandler);
  }

void HinDockTitle::markfunc(FXDockTitle *self){
  HinDockHandler::markfunc(self);
  if(self){
    HinGcMark(self->FXDockTitle::getFont());
    }
  }

void HinDrawable::markfunc(FXDrawable* drawable){
  HinId::markfunc(drawable);
  if(drawable) HinGcMark(drawable->FXDrawable::getVisual());
  }


void HinId::markfunc(FXId* self){
  HinObject::markfunc(self);
  if(self){
    HinGcMark(self->FXId::getApp());
    if(void *d=self->FXId::getUserData())
      MARK(d);
    }
  }


void HinCanvas::markfunc(FXCanvas* canvas){
  HinWindow::markfunc(canvas);
  }


void HinCheckButton::markfunc(FXCheckButton* cb){
  HinLabel::markfunc(cb);
  }


void HinColorDialog::markfunc(FXColorDialog* dlg){
  HinDialogBox::markfunc(dlg);
  }

void HinChoiceBox::markfunc(FXChoiceBox* box){
  HinDialogBox::markfunc(box);
  }

void HinWindow::markfunc(FXWindow* self){
  HinDrawable::markfunc(self);
  if(self){
    HinGcMark(self->FXWindow::getParent());
    HinGcMark(self->FXWindow::getOwner());
    HinGcMark(self->FXWindow::getShell());
    HinGcMark(self->FXWindow::getRoot());
    // HinGcMark(self->FXWindow::getNext());
    // HinGcMark(self->FXWindow::getPrev());
    HinGcMark(self->FXWindow::getFocus());
    HinGcMark(self->FXWindow::getTarget());
    HinGcMark(self->FXWindow::getAccelTable());
    HinGcMark(self->FXWindow::getDefaultCursor());
    HinGcMark(self->FXWindow::getDragCursor());

    // Mark child windows
    register FXWindow* child=self->FXWindow::getFirst();
    while(child!=NULL){
      HinGcMark(child);
      child=child->FXWindow::getNext();
      }
    }
  }


void HinDialogBox::markfunc(FXDialogBox* dlg){
  HinTopWindow::markfunc(dlg);
  }


void HinTopWindow::markfunc(FXTopWindow* top){
  HinShell::markfunc(top);
  if(top){
    HinGcMark(top->FXTopWindow::getIcon());
    HinGcMark(top->FXTopWindow::getMiniIcon());
    }
  }


void HinShell::markfunc(FXShell* shell){
  HinComposite::markfunc(shell);
  }


void HinComposite::markfunc(FXComposite* c){
  HinWindow::markfunc(c);
  }


void HinColorSelector::markfunc(FXColorSelector* cs){
  HinPacker::markfunc(cs);
  }


void HinPacker::markfunc(FXPacker* packer){
  HinComposite::markfunc(packer);
  }

void HinDockBar::markfunc(FXDockBar* dockbar){
  HinPacker::markfunc(dockbar);
  }

void HinDockSite::markfunc(FXDockSite* dockSite){
  HinPacker::markfunc(dockSite);
  }

void HinSpring::markfunc(FXSpring* self){
  HinPacker::markfunc(self);
  }


void HinHorizontalFrame::markfunc(FXHorizontalFrame* self){
  HinPacker::markfunc(self);
  }


void HinVerticalFrame::markfunc(FXVerticalFrame* self){
  HinPacker::markfunc(self);
  }


void HinGroupBox::markfunc(FXGroupBox* self){
  HinPacker::markfunc(self);
  if(self){
    HinGcMark(self->FXGroupBox::getFont());
    }
  }


void HinColorWell::markfunc(FXColorWell* cw){
  HinFrame::markfunc(cw);
  }


void HinComboBox::markfunc(FXComboBox* self){
  HinPacker::markfunc(self);
  if(self){
    HinGcMark(self->FXComboBox::getFont());
    for(FXint i=0; i<self->getNumItems(); i++){
      if(void *d=self->FXComboBox::getItemData(i))
        MARK(d);
      }
    }
  }


void HinCursor::markfunc(FXCursor* cursor){
  HinId::markfunc(cursor);
  }


void HinCursor::freefunc(FXCursor* self){
  delete_if_not_owned_by_app(self,reinterpret_cast<HinCursor*>(0));
  }


void HinApp::markfunc(FXApp *self){
  HinObject::markfunc(self);
  if(self){
    // Visuals
    HinGcMark(self->FXApp::getMonoVisual());
    HinGcMark(self->FXApp::getDefaultVisual());

    // Fonts
    HinGcMark(self->FXApp::getNormalFont());

    // Cursors
    HinGcMark(self->FXApp::getWaitCursor());
    HinGcMark(self->FXApp::getDefaultCursor(DEF_ARROW_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_RARROW_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_TEXT_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_HSPLIT_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_VSPLIT_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_XSPLIT_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_SWATCH_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_MOVE_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_DRAGH_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_DRAGV_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_DRAGTL_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_DRAGBR_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_DRAGTR_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_DRAGBL_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_DNDSTOP_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_DNDCOPY_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_DNDMOVE_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_DNDLINK_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_CROSSHAIR_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_CORNERNE_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_CORNERNW_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_CORNERSE_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_CORNERSW_CURSOR));
    HinGcMark(self->FXApp::getDefaultCursor(DEF_ROTATE_CURSOR));

    // Other windows
    HinGcMark(self->FXApp::getFocusWindow());
    HinGcMark(self->FXApp::getCursorWindow());

    /**
     * Root window is a special case; popups (like FXTooltip) can be created
     * without an "owner" by passing FXApp as the first argument to their
     * constructor, but in fact the "owner" of these window is the root window.
     * So unless we invoke HinRootWindow's mark function here, unowned windows
     * like tooltips may get garbage-collected prematurely.
     */
    if(self->FXApp::getRootWindow()){
      HinGcMark(self->FXApp::getRootWindow());
      HinRootWindow::markfunc(self->FXApp::getRootWindow());
      }

    // Registry
    HinGcMark(&(self->FXApp::reg()));

    // Timers, chores and signals are recycled and should never be destroyed
    }
  }


void HinArrowButton::markfunc(FXArrowButton *btn){
  HinFrame::markfunc(btn);
  }


void HinDataTarget::markfunc(FXDataTarget* obj){
  HinObject::markfunc(obj);
  }


void HinMainWindow::markfunc(FXMainWindow* obj){
  HinTopWindow::markfunc(obj);
  }


void HinTreeItem::markfunc(FXTreeItem* self){
  HinObject::markfunc(self);
  if(self){
    HinGcMark(self->FXTreeItem::getParent());
    HinGcMark(self->FXTreeItem::getNext());
    HinGcMark(self->FXTreeItem::getPrev());
    for(FXTreeItem* item=self->FXTreeItem::getFirst(); item; item=item->FXTreeItem::getNext()){
      HinGcMark(item);
      HinTreeItem::markfunc(item);
      }
    HinGcMark(self->FXTreeItem::getBelow());
    HinGcMark(self->FXTreeItem::getAbove());
    HinGcMark(self->FXTreeItem::getOpenIcon());
    HinGcMark(self->FXTreeItem::getClosedIcon());
    if(void *d=self->FXTreeItem::getData())
      MARK(d);
    }
  }


void HinTreeItem::freefunc(FXTreeItem* self){
  delete_if_not_owned(self,reinterpret_cast<HinTreeItem*>(0));
  }


void HinTreeList::markfunc(FXTreeList* self){
  HinScrollArea::markfunc(self);
  if(self){
    for(FXTreeItem* item=self->FXTreeList::getFirstItem(); item; item=item->FXTreeItem::getNext()){
      HinGcMark(item);
      HinTreeItem::markfunc(item);
      }
    HinGcMark(self->FXTreeList::getFont());
    }
  }


void HinFoldingItem::markfunc(FXFoldingItem* self){
  HinObject::markfunc(self);
  if(self){
    HinGcMark(self->FXFoldingItem::getParent());
    HinGcMark(self->FXFoldingItem::getNext());
    HinGcMark(self->FXFoldingItem::getPrev());
    for(FXFoldingItem* item=self->FXFoldingItem::getFirst(); item; item=item->FXFoldingItem::getNext()){
      HinGcMark(item);
      HinFoldingItem::markfunc(item);
      }
    HinGcMark(self->FXFoldingItem::getBelow());
    HinGcMark(self->FXFoldingItem::getAbove());
    HinGcMark(self->FXFoldingItem::getOpenIcon());
    HinGcMark(self->FXFoldingItem::getClosedIcon());
    if(void *d=self->FXFoldingItem::getData())
      MARK(d);
    }
  }


void HinFoldingItem::freefunc(FXFoldingItem* self){
  delete_if_not_owned(self,reinterpret_cast<HinFoldingItem*>(0));
  }


void HinFoldingList::markfunc(FXFoldingList* self){
  HinScrollArea::markfunc(self);
  if(self){
    for(FXFoldingItem* item=self->FXFoldingList::getFirstItem(); item; item=item->FXFoldingItem::getNext()){
      HinGcMark(item);
      HinFoldingItem::markfunc(item);
      }
    HinGcMark(self->FXFoldingList::getFont());
    }
  }


void HinListItem::markfunc(FXListItem* self){
  HinObject::markfunc(self);
  if(self){
    HinGcMark(self->FXListItem::getIcon());
    if(void *d=self->FXListItem::getData())
      MARK(d);
    }
  }


void HinListItem::freefunc(FXListItem* self){
  delete_if_not_owned(self,reinterpret_cast<HinListItem*>(0));
  }


void HinColorItem::markfunc(FXColorItem* self){
  HinListItem::markfunc(self);
  }


void HinColorItem::freefunc(FXColorItem* self){
  delete_if_not_owned(self,reinterpret_cast<HinColorItem*>(0));
  }


void HinList::markfunc(FXList* self){
  HinScrollArea::markfunc(self);
  if(self){
    for(FXint i=0;i<self->FXList::getNumItems();i++){
      FXListItem* item=self->FXList::getItem(i);
      HinGcMark(item);
      HinListItem::markfunc(item);
      }
    HinGcMark(self->FXList::getFont());
    }
  }


void HinColorList::markfunc(FXColorList* self){
  HinList::markfunc(self);
  }


void HinTableItem::markfunc(FXTableItem* self){
  HinObject::markfunc(self);
  if(self){
    HinGcMark(self->FXTableItem::getIcon());
    if(void* d=self->FXTableItem::getData())
      MARK(d);
    }
  }


void HinTableItem::freefunc(FXTableItem* self){
  delete_if_not_owned(self,reinterpret_cast<HinTableItem*>(0));
  }


void HinTable::markfunc(FXTable* self){
  HinScrollArea::markfunc(self);
  if(self){
    HinGcMark(self->FXTable::getFont());
    HinGcMark(self->FXTable::getRowHeaderFont());
    HinGcMark(self->FXTable::getColumnHeaderFont());
    for(FXint row=0;row<self->FXTable::getNumRows();row++){
      for(FXint col=0;col<self->FXTable::getNumColumns();col++){
        FXTableItem* item=self->FXTable::getItem(row,col);
        HinGcMark(item);
        }
      }
    }
  }


void HinHeaderItem::markfunc(FXHeaderItem* self){
  HinObject::markfunc(self);
  if(self){
    HinGcMark(self->FXHeaderItem::getIcon());
    if(void* d=self->FXHeaderItem::getData())
      MARK(d);
    }
  }


void HinHeaderItem::freefunc(FXHeaderItem* self){
  delete_if_not_owned(self,reinterpret_cast<HinHeaderItem*>(0));
  }


void HinHeader::markfunc(FXHeader* self){
  HinFrame::markfunc(self);
  if(self){
    for(FXint i=0;i<self->FXHeader::getNumItems();i++){
      FXHeaderItem* item=self->FXHeader::getItem(i);
      HinGcMark(item);
      HinHeaderItem::markfunc(item);
      }
    HinGcMark(self->FXHeader::getFont());
    }
  }


void HinIconItem::markfunc(FXIconItem* self){
  HinObject::markfunc(self);
  if(self){
    HinGcMark(self->FXIconItem::getBigIcon());
    HinGcMark(self->FXIconItem::getMiniIcon());
    if(void *d=self->FXIconItem::getData())
      MARK(d);
    }
  }


void HinIconItem::freefunc(FXIconItem* self){
  delete_if_not_owned(self,reinterpret_cast<HinIconItem*>(0));
  }


void HinIconList::markfunc(FXIconList* self){
  HinScrollArea::markfunc(self);
  if(self){
    HinGcMark(self->FXIconList::getHeader());
    for(FXint i=0;i<self->FXIconList::getNumItems();i++){
      FXIconItem* item=self->FXIconList::getItem(i);
      HinGcMark(item);
      HinIconItem::markfunc(item);
      }
    HinGcMark(self->FXIconList::getFont());
    }
  }


void HinDelegator::markfunc(FXDelegator* self){
  HinObject::markfunc(self);
  if(self){
    HinGcMark(self->FXDelegator::getDelegate());
    }
  }


void HinDebugTarget::markfunc(FXDebugTarget* self){
  HinObject::markfunc(self);
  }


void HinDict::markfunc(FXDict* self){
  HinObject::markfunc(self);
  }


void HinSettings::markfunc(FXSettings* self){
  HinDict::markfunc(self);
  }


void HinRegistry::markfunc(FXRegistry* self){
  HinSettings::markfunc(self);
  }


void HinStringDict::markfunc(FXStringDict* self){
  HinDict::markfunc(self);
  }


void HinRecentFiles::markfunc(FXRecentFiles* self){
  HinObject::markfunc(self);
  if(self){
    HinGcMark(self->FXRecentFiles::getTarget());
    }
  }


void HinScrollArea::markfunc(FXScrollArea* self){
  HinComposite::markfunc(self);
  if(self){
    HinGcMark(self->FXScrollArea::horizontalScrollBar());
    HinGcMark(self->FXScrollArea::verticalScrollBar());
    }
  }


void HinDocument::markfunc(FXDocument* self){
  HinObject::markfunc(self);
  }


void HinGLContext::markfunc(FXGLContext* self){
  HinObject::markfunc(self);
  if(self){
    HinGcMark(self->FXGLContext::getVisual());
    }
  }


void HinGLObject::markfunc(FXGLObject* self){
  HinObject::markfunc(self);
  }


void HinFont::markfunc(FXFont* self){
  HinId::markfunc(self);
  }


void HinFont::freefunc(FXFont *self){
  delete_if_not_owned_by_app(self,reinterpret_cast<HinFont*>(0));
  }


void HinIconDict::markfunc(FXIconDict* self){
  HinDict::markfunc(self);
  if(self){
    HinGcMark(self->FXIconDict::getIconSource());
    if(self->FXIconDict::no()>0){
      FXint pos=self->FXIconDict::first();
      FXint last=self->FXIconDict::last();
      while(pos<=last){
        const FXchar* name=self->FXIconDict::key(pos);
        FXIcon* icon=self->FXIconDict::find(name);
        HinGcMark(icon);
        pos=self->FXIconDict::next(pos);
        }
      }
    }
  }


void HinFileDict::markfunc(FXFileDict* self){
  HinDict::markfunc(self);
  HinGcMark(self->FXFileDict::getSettings());
  if(self){
    if(self->FXFileDict::no()>0){
      FXint pos=self->FXFileDict::first();
      FXint last=self->FXFileDict::last();
      while(pos<=last){
        const FXchar* key=self->FXFileDict::key(pos);
        FXFileAssoc* assoc=self->FXFileDict::find(key);
        HinGcMark(assoc);
        pos=self->FXFileDict::next(pos);
        }
      }
    }
  }


void HinDial::markfunc(FXDial* self){
  FXTRACE((100,"HinDial::markfunc() %p\n",self));
  HinFrame::markfunc(self);
  }


void HinDragCorner::markfunc(FXDragCorner* self){
  FXTRACE((100,"HinDragCorner::markfunc() %p\n",self));
  HinWindow::markfunc(self);
  }


void HinDirItem::markfunc(FXDirItem* self){
  FXTRACE((100,"HinDirItem::markfunc() %p\n",self));
  HinTreeItem::markfunc(self);
  if(self){
    HinGcMark(self->FXDirItem::getAssoc());
    }
  }


void HinDirItem::freefunc(FXDirItem* self){
  delete_if_not_owned(self,reinterpret_cast<HinDirItem*>(0));
  }

void HinDirList::markfunc(FXDirList* self){
  FXTRACE((100,"HinDirList::markfunc() %p\n",self));
  HinTreeList::markfunc(self);
  if(self){
    HinGcMark(self->FXDirList::getAssociations());
    }
  }


void Hin4Splitter::markfunc(FX4Splitter* self){
  FXTRACE((100,"Hin4Splitter::markfunc() %p\n",self));
  HinComposite::markfunc(self);
  if(self){
    HinGcMark(self->FX4Splitter::getTopLeft());
    HinGcMark(self->FX4Splitter::getTopRight());
    HinGcMark(self->FX4Splitter::getBottomLeft());
    HinGcMark(self->FX4Splitter::getBottomRight());
    }
  }


void HinFileItem::markfunc(FXFileItem* self){
  FXTRACE((100,"HinFileItem::markfunc() %p\n",self));
  HinIconItem::markfunc(self);
  if(self){
    HinGcMark(self->FXFileItem::getAssoc());
    }
  }


void HinFileItem::freefunc(FXFileItem* self){
  delete_if_not_owned(self,reinterpret_cast<HinFileItem*>(0));
  }


void HinFileList::markfunc(FXFileList* self){
  FXTRACE((100,"HinFileList::markfunc() %p\n",self));
  HinIconList::markfunc(self);
  if(self){
    HinGcMark(self->FXFileList::getAssociations());
    for(FXint i=0;i<self->FXFileList::getNumItems();i++){
      FXFileAssoc* assoc=self->FXFileList::getItemAssoc(i);
      HinGcMark(assoc);
      }
    }
  }


void HinDirBox::markfunc(FXDirBox* self){
  FXTRACE((100,"HinDirBox::markfunc() %p\n",self));
  HinTreeListBox::markfunc(self);
  }


void HinDriveBox::markfunc(FXDriveBox* self){
  FXTRACE((100,"HinDriveBox::markfunc() %p\n",self));
  HinListBox::markfunc(self);
  }


void HinDirSelector::markfunc(FXDirSelector* self){
  FXTRACE((100,"HinDirSelector::markfunc() %p\n",self));
  HinPacker::markfunc(self);
  if(self){
    HinGcMark(self->FXDirSelector::acceptButton());
    HinGcMark(self->FXDirSelector::cancelButton());
    }
  }


void HinFileSelector::markfunc(FXFileSelector* self){
  FXTRACE((100,"HinFileSelector::markfunc() %p\n",self));
  HinPacker::markfunc(self);
  if(self){
    HinGcMark(self->FXFileSelector::acceptButton());
    HinGcMark(self->FXFileSelector::cancelButton());
    }
  }


void HinFontSelector::markfunc(FXFontSelector* self){
  FXTRACE((100,"HinFontSelector::markfunc() %p\n",self));
  HinPacker::markfunc(self);
  if(self){
    HinGcMark(self->FXFontSelector::acceptButton());
    HinGcMark(self->FXFontSelector::cancelButton());
    }
  }


void HinDirDialog::markfunc(FXDirDialog* self){
  FXTRACE((100,"HinDirDialog::markfunc() %p\n",self));
  HinDialogBox::markfunc(self);
  }


void HinFileDialog::markfunc(FXFileDialog* self){
  FXTRACE((100,"HinFileDialog::markfunc() %p\n",self));
  HinDialogBox::markfunc(self);
  }


void HinFontDialog::markfunc(FXFontDialog* self){
  FXTRACE((100,"HinFontDialog::markfunc() %p\n",self));
  HinDialogBox::markfunc(self);
  }


void HinListBox::markfunc(FXListBox* self){
  FXTRACE((100,"HinListBox::markfunc() %p\n",self));
  HinPacker::markfunc(self);
  if(self){
    HinGcMark(self->FXListBox::getFont());
    for(FXint i=0;i<self->FXListBox::getNumItems();i++){
      HinGcMark(self->FXListBox::getItemIcon(i));
      if(self->FXListBox::getItemData(i))
        MARK(self->FXListBox::getItemData(i));
      }
    }
  }


void HinTreeListBox::markfunc(FXTreeListBox* self){
  FXTRACE((100,"HinTreeListBox::markfunc() %p\n",self));
  HinPacker::markfunc(self);
  if(self){
    HinGcMark(self->FXTreeListBox::getFont());
    for(FXTreeItem* item=self->FXTreeListBox::getFirstItem();item!=0;item=item->FXTreeItem::getNext()){
      HinGcMark(item);
      HinTreeItem::markfunc(item);
      }
    }
  }


void HinToolTip::markfunc(FXToolTip* self){
  FXTRACE((100,"HinToolTip::markfunc() %p\n",self));
  HinShell::markfunc(self);
  if(self){
    HinGcMark(self->FXToolTip::getFont());
    }
  }


void HinRootWindow::markfunc(FXRootWindow* self){
  FXTRACE((100,"HinRootWindow::markfunc() %p\n",self));
  HinComposite::markfunc(self);
  }


void HinPNGIcon::markfunc(FXPNGIcon *self){
  FXTRACE((100,"HinPNGIcon::markfunc() %p\n",self));
  HinIcon::markfunc(self);
  }


void HinMDIMenu::markfunc(FXMDIMenu *self){
  FXTRACE((100,"HinMDIMenu::markfunc() %p\n",self));
  HinMenuPane::markfunc(self);
  }


void HinMDIRestoreButton::markfunc(FXMDIRestoreButton *self){
  FXTRACE((100,"HinMDIRestoreButton::markfunc() %p\n",self));
  HinButton::markfunc(self);
  }


void HinXBMImage::markfunc(FXXBMImage *self){
  FXTRACE((100,"HinXBMImage::markfunc() %p\n",self));
  HinImage::markfunc(self);
  }


void HinXPMImage::markfunc(FXXPMImage *self){
  FXTRACE((100,"HinXPMImage::markfunc() %p\n",self));
  HinImage::markfunc(self);
  }


void HinJPGImage::markfunc(FXJPGImage *self){
  FXTRACE((100,"HinJPGImage::markfunc() %p\n",self));
  HinImage::markfunc(self);
  }


void HinTextField::markfunc(FXTextField *self){
  FXTRACE((100,"HinTextField::markfunc() %p\n",self));
  HinFrame::markfunc(self);
  if(self){
    HinGcMark(self->FXTextField::getFont());
    }
  }


void HinMenuCascade::markfunc(FXMenuCascade *self){
  FXTRACE((100,"HinMenuCascade::markfunc() %p\n",self));
  HinMenuCaption::markfunc(self);
  if(self){
    HinGcMark(self->FXMenuCascade::getMenu());
    }
  }


void HinMenuCommand::markfunc(FXMenuCommand *self){
  FXTRACE((100,"HinMenuCommand::markfunc() %p\n",self));
  HinMenuCaption::markfunc(self);
  }


void HinMenuBar::markfunc(FXMenuBar *self){
  FXTRACE((100,"HinMenuBar::markfunc() %p\n",self));
  HinToolBar::markfunc(self);
  }


void HinScrollCorner::markfunc(FXScrollCorner *self){
  FXTRACE((100,"HinScrollCorner::markfunc() %p\n",self));
  HinWindow::markfunc(self);
  }


void HinShutter::markfunc(FXShutter *self){
  HinVerticalFrame::markfunc(self);
  }


void HinProgressBar::markfunc(FXProgressBar *self){
  FXTRACE((100,"HinProgressBar::markfunc() %p\n",self));
  HinFrame::markfunc(self);
  if(self){
    HinGcMark(self->FXProgressBar::getFont());
    }
  }


void HinSeparator::markfunc(FXSeparator* self){
  FXTRACE((100,"HinSeparator::markfunc() %p\n",self));
  HinFrame::markfunc(self);
 }


void HinHorizontalSeparator::markfunc(FXHorizontalSeparator *self){
  FXTRACE((100,"HinHorizontalSeparator::markfunc() %p\n",self));
  HinSeparator::markfunc(self);
  }


void HinSpinner::markfunc(FXSpinner *self){
  FXTRACE((100,"HinSpinner::markfunc() %p\n",self));
  HinPacker::markfunc(self);
  if(self){
    HinGcMark(self->FXSpinner::getFont());
    }
  }


void HinRealSpinner::markfunc(FXRealSpinner *self){
  FXTRACE((100,"HinRealSpinner::markfunc() %p\n",self));
  HinPacker::markfunc(self);
  if(self){
    HinGcMark(self->FXRealSpinner::getFont());
    }
  }


void HinGIFIcon::markfunc(FXGIFIcon *self){
  FXTRACE((100,"HinGIFIcon::markfunc() %p\n",self));
  HinIcon::markfunc(self);
  }


void HinTIFIcon::markfunc(FXTIFIcon *self){
  FXTRACE((100,"HinTIFIcon::markfunc() %p\n",self));
  HinIcon::markfunc(self);
  }


void HinPCXIcon::markfunc(FXPCXIcon *self){
  FXTRACE((100,"HinPCXIcon::markfunc() %p\n",self));
  HinIcon::markfunc(self);
  }


void HinRGBIcon::markfunc(FXRGBIcon *self){
  FXTRACE((100,"HinRGBIcon::markfunc() %p\n",self));
  HinIcon::markfunc(self);
  }


void HinMDIMaximizeButton::markfunc(FXMDIMaximizeButton *self){
  FXTRACE((100,"HinMDIMaximizeButton::markfunc() %p\n",self));
  HinButton::markfunc(self);
  }


void HinMDIDeleteButton::markfunc(FXMDIDeleteButton *self){
  FXTRACE((100,"HinMDIDeleteButton::markfunc() %p\n",self));
  HinButton::markfunc(self);
  }


void HinMenuButton::markfunc(FXMenuButton *self){
  FXTRACE((100,"HinMenuButton::markfunc() %p\n",self));
  HinLabel::markfunc(self);
  if(self){
    HinGcMark(self->FXMenuButton::getMenu());
    }
  }


void HinMatrix::markfunc(FXMatrix *self){
  FXTRACE((100,"HinMatrix::markfunc() %p\n",self));
  HinPacker::markfunc(self);
  }


void HinMenuSeparator::markfunc(FXMenuSeparator *self){
  FXTRACE((100,"HinMenuSeparator::markfunc() %p\n",self));
  HinWindow::markfunc(self);
  }


void HinSwitcher::markfunc(FXSwitcher *self){
  FXTRACE((100,"HinSwitcher::markfunc() %p\n",self));
  HinPacker::markfunc(self);
  }


void HinRealSlider::markfunc(FXRealSlider *self){
  FXTRACE((100,"HinRealSlider::markfunc() %p\n",self));
  HinFrame::markfunc(self);
  }


void HinSlider::markfunc(FXSlider *self){
  FXTRACE((100,"HinSlider::markfunc() %p\n",self));
  HinFrame::markfunc(self);
  }


void HinToolBarGrip::markfunc(FXToolBarGrip *self){
  FXTRACE((100,"HinToolBarGrip::markfunc() %p\n",self));
  HinDockHandler::markfunc(self);
  }


void HinJPGIcon::markfunc(FXJPGIcon *self){
  FXTRACE((100,"HinJPGIcon::markfunc() %p\n",self));
  HinIcon::markfunc(self);
  }


void HinTabBar::markfunc(FXTabBar *self){
  FXTRACE((100,"HinTabBar::markfunc() %p\n",self));
  HinPacker::markfunc(self);
  }


void HinToolBarTab::markfunc(FXToolBarTab *self){
  FXTRACE((100,"HinToolBarTab::markfunc() %p\n",self));
  HinFrame::markfunc(self);
  }


void HinSearchDialog::markfunc(FXSearchDialog *self){
  FXTRACE((100,"HinSearchDialog::markfunc() %p\n",self));
  HinDialogBox::markfunc(self);
  }


void HinPrintDialog::markfunc(FXPrintDialog *self){
  FXTRACE((100,"HinPrintDialog::markfunc() %p\n",self));
  HinDialogBox::markfunc(self);
  }


void HinMDIMinimizeButton::markfunc(FXMDIMinimizeButton *self){
  FXTRACE((100,"HinMDIMinimizeButton::markfunc() %p\n",self));
  HinButton::markfunc(self);
  }


void HinGIFCursor::markfunc(FXGIFCursor *self){
  FXTRACE((100,"HinGIFCursor::markfunc() %p\n",self));
  HinCursor::markfunc(self);
  }


void HinGIFCursor::freefunc(FXGIFCursor* self){
  delete_if_not_owned_by_app(self,reinterpret_cast<HinGIFCursor*>(0));
  }


void HinCURCursor::markfunc(FXCURCursor *self){
  FXTRACE((100,"HinCURCursor::markfunc() %p\n",self));
  HinCursor::markfunc(self);
  }


void HinCURCursor::freefunc(FXCURCursor* self){
  delete_if_not_owned_by_app(self,reinterpret_cast<HinCURCursor*>(0));
  }


void HinGLViewer::markfunc(FXGLViewer *self){
  FXTRACE((100,"HinGLViewer::markfunc() %p\n",self));
  HinGLCanvas::markfunc(self);
  if(self){
    HinGcMark(self->FXGLViewer::getScene());
    HinGcMark(self->FXGLViewer::getSelection());
    }
  }


void HinGIFImage::markfunc(FXGIFImage *self){
  FXTRACE((100,"HinGIFImage::markfunc() %p\n",self));
  HinImage::markfunc(self);
  }


void HinTIFImage::markfunc(FXTIFImage *self){
  FXTRACE((100,"HinTIFImage::markfunc() %p\n",self));
  HinImage::markfunc(self);
  }


void HinPCXImage::markfunc(FXPCXImage *self){
  FXTRACE((100,"HinPCXImage::markfunc() %p\n",self));
  HinImage::markfunc(self);
  }


void HinRGBImage::markfunc(FXRGBImage *self){
  FXTRACE((100,"HinRGBImage::markfunc() %p\n",self));
  HinImage::markfunc(self);
  }


void HinMenuPane::markfunc(FXMenuPane *self){
  FXTRACE((100,"HinMenuPane::markfunc() %p\n",self));
  HinPopup::markfunc(self);
  }


void HinScrollPane::markfunc(FXScrollPane *self){
  HinMenuPane::markfunc(self);
  }


void HinSplitter::markfunc(FXSplitter *self){
  FXTRACE((100,"HinSplitter::markfunc() %p\n",self));
  HinComposite::markfunc(self);
  }


void HinStatusBar::markfunc(FXStatusBar *self){
  FXTRACE((100,"HinStatusBar::markfunc() %p\n",self));
  HinHorizontalFrame::markfunc(self);
  if(self){
    HinGcMark(self->FXStatusBar::getStatusLine());
    HinGcMark(self->FXStatusBar::getDragCorner());
    }
  }


void HinMDIChild::markfunc(FXMDIChild *self){
  FXTRACE((100,"HinMDIChild::markfunc() %p\n",self));
  HinComposite::markfunc(self);
  if(self){
    HinGcMark(self->FXMDIChild::contentWindow());
    HinGcMark(self->FXMDIChild::getIcon());
    HinGcMark(self->FXMDIChild::getMenu());
    HinGcMark(self->FXMDIChild::getFont());
    }
  }


void HinPNGImage::markfunc(FXPNGImage *self){
  FXTRACE((100,"HinPNGImage::markfunc() %p\n",self));
  HinImage::markfunc(self);
  }


void HinVisual::markfunc(FXVisual *self){
  FXTRACE((100,"HinVisual::markfunc() %p\n",self));
  HinId::markfunc(self);
  }


void HinVisual::freefunc(FXVisual *self){
  delete_if_not_owned_by_app(self,reinterpret_cast<HinVisual*>(0));
  }


void HinVerticalSeparator::markfunc(FXVerticalSeparator *self){
  FXTRACE((100,"HinVerticalSeparator::markfunc() %p\n",self));
  HinSeparator::markfunc(self);
  }


void HinToggleButton::markfunc(FXToggleButton *self){
  FXTRACE((100,"HinToggleButton::markfunc() %p\n",self));
  HinLabel::markfunc(self);
  if(self){
    HinGcMark(self->FXToggleButton::getAltIcon());
    }
  }


void HinTriStateButton::markfunc(FXTriStateButton *self){
  FXTRACE((100,"HinTriStateButton::markfunc() %p\n",self));
  HinToggleButton::markfunc(self);
  if(self){
    HinGcMark(self->FXTriStateButton::getMaybeIcon());
    }
  }


void HinPopup::markfunc(FXPopup *self){
  FXTRACE((100,"HinPopup::markfunc() %p\n",self));
  HinShell::markfunc(self);
  if(self){
    HinGcMark(self->FXPopup::getGrabOwner());
    }
  }


void HinOptionMenu::markfunc(FXOptionMenu *self){
  FXTRACE((100,"HinOptionMenu::markfunc() %p\n",self));
  HinLabel::markfunc(self);
  if(self){
    HinGcMark(self->FXOptionMenu::getCurrent());
    HinGcMark(self->FXOptionMenu::getMenu());
    }
  }


void HinMessageBox::markfunc(FXMessageBox *self){
  FXTRACE((100,"HinMessageBox::markfunc() %p\n",self));
  HinDialogBox::markfunc(self);
  }


void HinToolBar::markfunc(FXToolBar *self){
  FXTRACE((100,"HinToolBar::markfunc() %p\n",self));
  HinPacker::markfunc(self);
  if(self){
    HinGcMark(self->FXToolBar::getDryDock());
    HinGcMark(self->FXToolBar::getWetDock());
    }
  }


void HinGLCanvas::markfunc(FXGLCanvas *self){
  FXTRACE((100,"HinGLCanvas::markfunc() %p\n",self));
  HinCanvas::markfunc(self);
  }


void HinGLVisual::markfunc(FXGLVisual *self){
  FXTRACE((100,"HinGLVisual::markfunc() %p\n",self));
  HinVisual::markfunc(self);
  }


void HinGLVisual::freefunc(FXGLVisual *self){
  delete_if_not_owned_by_app(self,reinterpret_cast<HinGLVisual*>(0));
  }


void HinOption::markfunc(FXOption *self){
  FXTRACE((100,"HinOption::markfunc() %p\n",self));
  HinLabel::markfunc(self);
  }


void HinScrollWindow::markfunc(FXScrollWindow *self){
  FXTRACE((100,"HinScrollWindow::markfunc() %p\n",self));
  HinScrollArea::markfunc(self);
  if(self){
    HinGcMark(self->FXScrollWindow::contentWindow());
    }
  }


void HinText::markfunc(FXText *self){
  FXTRACE((100,"HinText::markfunc() %p\n",self));
  HinScrollArea::markfunc(self);
  if(self){
    HinGcMark(self->FXText::getFont());
    }
  }


void HinToolBarShell::markfunc(FXToolBarShell *self){
  FXTRACE((100,"HinToolBarShell::markfunc() %p\n",self));
  HinTopWindow::markfunc(self);
  }

void HinSplashWindow::markfunc(FXSplashWindow *self){
  FXTRACE((100,"HinSplashWindow::markfunc() %p\n",self));
  HinTopWindow::markfunc(self);
  if(self){
    HinGcMark(self->FXSplashWindow::getIcon());
    }
  }

void HinInputDialog::markfunc(FXInputDialog *self){
  FXTRACE((100,"HinInputDialog::markfunc() %p\n",self));
  HinDialogBox::markfunc(self);
  }


void HinMDIClient::markfunc(FXMDIClient *self){
  FXTRACE((100,"HinMDIClient::markfunc() %p\n",self));
  HinComposite::markfunc(self);
  }


void HinMenuTitle::markfunc(FXMenuTitle *self){
  FXTRACE((100,"HinMenuTitle::markfunc() %p\n",self));
  HinMenuCaption::markfunc(self);
  if(self){
    HinGcMark(self->FXMenuTitle::getMenu());
    }
  }


/*
void HinBitmapView::markfunc(FXBitmapView *self){
  HinScrollArea::markfunc(self);
  if(self){
    HinGcMark(self->getBitmap());
    }
  }
*/


void HinImageView::markfunc(FXImageView *self){
  HinScrollArea::markfunc(self);
  if(self){
    HinGcMark(self->FXImageView::getImage());
    }
  }


void HinShutterItem::markfunc(FXShutterItem *self){
  HinVerticalFrame::markfunc(self);
  if(self){
    HinGcMark(self->FXShutterItem::getButton());
    HinGcMark(self->FXShutterItem::getContent());
    }
  }


void HinMDIWindowButton::markfunc(FXMDIWindowButton *self){
  FXTRACE((100,"HinMDIWindowButton::markfunc() %p\n",self));
  HinMenuButton::markfunc(self);
  }


void HinMenuCaption::markfunc(FXMenuCaption *self){
  FXTRACE((100,"HinMenuCaption::markfunc() %p\n",self));
  HinWindow::markfunc(self);
  if(self){
    HinGcMark(self->FXMenuCaption::getFont());
    HinGcMark(self->FXMenuCaption::getIcon());
    }
  }


void HinTabItem::markfunc(FXTabItem *self){
  FXTRACE((100,"HinTabItem::markfunc() %p\n",self));
  HinLabel::markfunc(self);
  }


void HinStatusLine::markfunc(FXStatusLine *self){
  FXTRACE((100,"HinStatusLine::markfunc() %p\n",self));
  HinFrame::markfunc(self);
  if(self){
    HinGcMark(self->FXStatusLine::getFont());
    }
  }


void HinGLShape::markfunc(FXGLShape *self){
  FXTRACE((100,"HinGLShape::markfunc() %p\n",self));
  HinGLObject::markfunc(self);
  }


void HinTabBook::markfunc(FXTabBook *self){
  FXTRACE((100,"HinTabBook::markfunc() %p\n",self));
  HinTabBar::markfunc(self);
  }


void HinReplaceDialog::markfunc(FXReplaceDialog *self){
  FXTRACE((100,"HinReplaceDialog::markfunc() %p\n",self));
  HinDialogBox::markfunc(self);
  }


void HinXBMIcon::markfunc(FXXBMIcon *self){
  FXTRACE((100,"HinXBMIcon::markfunc() %p\n",self));
  HinIcon::markfunc(self);
  }


void HinXPMIcon::markfunc(FXXPMIcon *self){
  FXTRACE((100,"HinXPMIcon::markfunc() %p\n",self));
  HinIcon::markfunc(self);
  }


void HinRadioButton::markfunc(FXRadioButton *self){
  FXTRACE((100,"HinRadioButton::markfunc() %p\n",self));
  HinLabel::markfunc(self);
  }


void HinScrollBar::markfunc(FXScrollBar *self){
  FXTRACE((100,"HinScrollBar::markfunc() %p\n",self));
  HinWindow::markfunc(self);
  }


void HinStream::markfunc(FXStream *self){
  FXTRACE((100,"HinStream::markfunc() %p\n",self));
  if(self){
    HinGcMark((void*)self->FXStream::container());
    }
  }


void HinFileStream::markfunc(FXFileStream *self){
  FXTRACE((100,"HinFileStream::markfunc() %p\n",self));
  HinStream::markfunc(self);
  }


void HinMemoryStream::markfunc(FXMemoryStream *self){
  FXTRACE((100,"HinMemoryStream::markfunc() %p\n",self));
  HinStream::markfunc(self);
  }


void HinDC::markfunc(FXDC *self){
  FXTRACE((100,"HinDC::markfunc() %p\n",self));
  }


void HinDCWindow::markfunc(FXDCWindow *self){
  FXTRACE((100,"HinDCWindow::markfunc() %p\n",self));
  HinDC::markfunc(self);
  }


void HinDCPrint::markfunc(FXDCPrint *self){
  FXTRACE((100,"HinDCPrint::markfunc() %p\n",self));
  HinDC::markfunc(self);
  }


void HinProgressDialog::markfunc(FXProgressDialog* self){
  FXTRACE((100,"HinProgressDialog::markfunc() %p\n",self));
  HinDialogBox::markfunc(self);
  }


void HinPicker::markfunc(FXPicker* self){
  FXTRACE((100,"HinPicker::markfunc() %p\n",self));
  HinButton::markfunc(self);
  }


void HinColorBar::markfunc(FXColorBar* self){
  FXTRACE((100,"HinColorBar::markfunc() %p\n",self));
  HinFrame::markfunc(self);
  }


void HinColorRing::markfunc(FXColorRing* self){
  FXTRACE((100,"HinColorRing::markfunc() %p\n",self));
  HinFrame::markfunc(self);
  }


void HinColorWheel::markfunc(FXColorWheel* self){
  FXTRACE((100,"HinColorWheel::markfunc() %p\n",self));
  HinFrame::markfunc(self);
  }


void HinICOIcon::markfunc(FXICOIcon* self){
  FXTRACE((100,"HinICOIcon::markfunc() %p\n",self));
  HinIcon::markfunc(self);
  }


void HinICOImage::markfunc(FXICOImage* self){
  FXTRACE((100,"HinICOImage::markfunc() %p\n",self));
  HinImage::markfunc(self);
  }


void HinTGAIcon::markfunc(FXTGAIcon* self){
  FXTRACE((100,"HinTGAIcon::markfunc() %p\n",self));
  HinIcon::markfunc(self);
  }


void HinTGAImage::markfunc(FXTGAImage* self){
  FXTRACE((100,"HinTGAImage::markfunc() %p\n",self));
  HinImage::markfunc(self);
  }


void HinBitmapFrame::markfunc(FXBitmapFrame* self){
  FXTRACE((100,"start HinBitmapFrame::markfunc(%p)\n",self));
  HinFrame::markfunc(self);
  if(self!=0){
    HinGcMark(self->FXBitmapFrame::getBitmap());
    }
  FXTRACE((100,"end HinBitmapFrame::markfunc(%p)\n",self));
  }


void HinImageFrame::markfunc(FXImageFrame* self){
  FXTRACE((100,"start HinImageFrame::markfunc(%p)\n",self));
  HinFrame::markfunc(self);
  if(self!=0){
    HinGcMark(self->FXImageFrame::getImage());
    }
  FXTRACE((100,"end HinImageFrame::markfunc(%p)\n",self));
  }


void HinGradientBar::markfunc(FXGradientBar* self){
  FXTRACE((100,"start HinGradientBar::markfunc(%p)\n",self));
  HinFrame::markfunc(self);
  FXTRACE((100,"end HinGradientBar::markfunc(%p)\n",self));
  }

#ifdef WITH_FXSCINTILLA

void HinScintilla::markfunc(FXScintilla* self){
  FXTRACE((100,"HinScintilla::markfunc() %p\n",self));
  HinScrollArea::markfunc(self);
  }

#endif

void HinWizard::markfunc(FXWizard* self){
  FXTRACE((100,"HinWizard::markfunc() %p\n",self));
  HinDialogBox::markfunc(self);
  if(self){
    HinGcMark(self->FXWizard::advanceButton());
    HinGcMark(self->FXWizard::retreatButton());
    HinGcMark(self->FXWizard::finishButton());
    HinGcMark(self->FXWizard::cancelButton());
    HinGcMark(self->FXWizard::getContainer());
    HinGcMark(self->FXWizard::getImage());
    }
  }


void HinRuler::markfunc(FXRuler* self){
  FXTRACE((100,"HinRuler::markfunc() %p\n",self));
  HinFrame::markfunc(self);
  if(self){
    HinGcMark(self->FXRuler::getFont());
    }
  }


void HinRulerView::markfunc(FXRulerView* self){
  FXTRACE((100,"HinRulerView::markfunc() %p\n",self));
  HinScrollArea::markfunc(self);
  if(self){
    HinGcMark(self->FXRulerView::horizontalRuler());
    HinGcMark(self->FXRulerView::verticalRuler());
    HinGcMark(self->FXRulerView::getHRulerFont());
    HinGcMark(self->FXRulerView::getVRulerFont());
    }
  }


void HinPPMIcon::markfunc(FXPPMIcon* self){
  FXTRACE((100,"HinPPMIcon::markfunc() %p\n",self));
  HinIcon::markfunc(self);
  }


void HinPPMImage::markfunc(FXPPMImage* self){
  FXTRACE((100,"HinPPMImage::markfunc() %p\n",self));
  HinImage::markfunc(self);
  }

