/***********************************************************************
 * $Id: unregisterOwnedObjects.cpp 2911 2008-12-11 14:09:45Z lyle $
 ***********************************************************************/

/**
 * The purpose of an unregisterOwnedObjects() function for a particular
 * class is to call HinUnregisterRubyObj() on any objects that this object
 * created itself, and which it "owns" and will destroy in its destructor.
 * This includes not only child widgets, like the horizontal and vertical
 * scrollbars managed by an FXScrollArea, but other non-widget objects
 * like list items.
 *
 * You don't need to worry about objects that the user created himself
 * using Ruby code, because those should get unregistered automatically
 * when they're destroyed. So, for example, if I create a button as a child
 * of a frame, e.g.
 *
 *     FXButton.new(parentFrame, ...)
 *
 * that Ruby object's peer is an HinButton instance, and the destructor for
 * the HinButton class calls HinUnregisterRubyObj(this). We only need to
 * worry about the C++ objects that aren't subclasses of regular FOX classes,
 * but which have somehow been "exposed" to the Ruby layer.
 */

#include "HinCommon.h"

void HinHeader::unregisterOwnedObjects(FXHeader *self)
{
    // HinFrame::unregisterOwnedObjects(self);
    for (FXint i = 0; i < self->getNumItems(); i++) HinUnregisterRubyObj(self->getItem(i));
}

void HinScrollArea::unregisterOwnedObjects(FXScrollArea *self)
{
    // HinComposite::unregisterOwnedObjects(self);
    HinUnregisterRubyObj(self->horizontalScrollBar());
    HinUnregisterRubyObj(self->verticalScrollBar());
}

/*
void HinBitmapView::unregisterOwnedObjects(FXBitmapView *self)
{
    HinScrollArea::unregisterOwnedObjects(self);
}
*/

void HinFoldingList::unregisterOwnedObjects(FXFoldingList *self)
{
    HinScrollArea::unregisterOwnedObjects(self);
    HinUnregisterRubyObj(self->getHeader());

    // Save pointer(s) to the soon-to-be-destroyed items
    FXObjectListOf<FXFoldingItem> items;
    HinFoldingList::enumerateItems(self->getFirstItem(),self->getLastItem(),items);

    // Now zero-out pointers held by still-alive Ruby objects
    for (FXint i = 0; i <items.no(); i++) HinUnregisterRubyObj(items[i]);
}

void HinIconList::unregisterOwnedObjects(FXIconList *self)
{
    HinScrollArea::unregisterOwnedObjects(self);
    HinUnregisterRubyObj(self->getHeader());
    for (FXint i = 0; i <self->getNumItems(); i++) HinUnregisterRubyObj(self->getItem(i));
}

void HinImageView::unregisterOwnedObjects(FXImageView *self)
{
    HinScrollArea::unregisterOwnedObjects(self);
}

void HinList::unregisterOwnedObjects(FXList *self)
{
    HinScrollArea::unregisterOwnedObjects(self);
    for (FXint i = 0; i < self->getNumItems(); i++) HinUnregisterRubyObj(self->getItem(i));
}

void HinColorList::unregisterOwnedObjects(FXColorList *self)
{
    HinList::unregisterOwnedObjects(self);
}

void HinScrollWindow::unregisterOwnedObjects(FXScrollWindow *self)
{
    HinScrollArea::unregisterOwnedObjects(self);
}

void HinTable::unregisterOwnedObjects(FXTable *self)
{
    FXint r,c;
    HinScrollArea::unregisterOwnedObjects(self);
    HinHeader::unregisterOwnedObjects(self->getRowHeader());
    HinHeader::unregisterOwnedObjects(self->getColumnHeader());
    HinUnregisterRubyObj(self->getRowHeader());
    HinUnregisterRubyObj(self->getColumnHeader());
    for(r=0; r<self->getNumRows(); r++){
      for(c=0; c<self->getNumColumns(); c++){
        HinUnregisterRubyObj(self->getItem(r,c));
        }
      }
}

void HinText::unregisterOwnedObjects(FXText *self)
{
    HinScrollArea::unregisterOwnedObjects(self);
}

void HinTreeList::unregisterOwnedObjects(FXTreeList *self)
{
    HinScrollArea::unregisterOwnedObjects(self);

    // Save pointer(s) to the soon-to-be-destroyed items
    FXObjectListOf<FXTreeItem> items;
    HinTreeList::enumerateItems(self->getFirstItem(), self->getLastItem(), items);

    // Now zero-out pointers held by still-alive Ruby objects
    for (FXint i = 0; i < items.no(); i++) HinUnregisterRubyObj(items[i]);
}
