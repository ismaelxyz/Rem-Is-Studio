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

/**
 * The default protocol for what happens to objects at garbage-collection
 * time is defined by HinObject::freefunc, and it is associated with
 * all of the classes as part of the DO_CLASS_SETUP macro (see exceptions.i).
 */

/**
 * Special cases.
 */

%freefunc FXCursor "HinCursor::freefunc";
%freefunc FXCURCursor "HinCURCursor::freefunc";
%freefunc FXGIFCursor "HinGIFCursor::freefunc";
%freefunc FXGLVisual "HinGLVisual::freefunc";
%freefunc FXColorItem "HinColorItem::freefunc";
%freefunc FXDirItem "HinDirItem::freefunc";
%freefunc FXFileItem "HinFileItem::freefunc";
%freefunc FXFoldingItem "HinFoldingItem::freefunc";
%freefunc FXFont "HinFont::freefunc";
%freefunc FXHeaderItem "HinHeaderItem::freefunc";
%freefunc FXIconItem "HinIconItem::freefunc";
%freefunc FXListItem "HinListItem::freefunc";
%freefunc FXTableItem "HinTableItem::freefunc";
%freefunc FXTreeItem "HinTreeItem::freefunc";
%freefunc FXVisual "HinVisual::freefunc";

/**
 * Other structs and classes not derived from FXObject.
 * Just unregister these.
 */

%freefunc FXChore "HinUnregisterRubyObj";
%freefunc FXDC "HinUnregisterRubyObj";
%freefunc FXDCPrint "HinUnregisterRubyObj";
%freefunc FXEvent "HinUnregisterRubyObj";
%freefunc FXExtentd "HinUnregisterRubyObj";
%freefunc FXExtentf "HinUnregisterRubyObj";
%freefunc FXFileAssoc "HinUnregisterRubyObj";
%freefunc FXFileStream "HinUnregisterRubyObj";
%freefunc FXFontDesc "HinUnregisterRubyObj";
%freefunc FXLight "HinUnregisterRubyObj";
%freefunc FXMat3d "HinUnregisterRubyObj";
%freefunc FXMat3f "HinUnregisterRubyObj";
%freefunc FXMat4d "HinUnregisterRubyObj";
%freefunc FXMat4f "HinUnregisterRubyObj";
%freefunc FXMaterial "HinUnregisterRubyObj";
%freefunc FXMemoryStream "HinUnregisterRubyObj";
%freefunc FXPoint "HinUnregisterRubyObj";
%freefunc FXPrinter "HinUnregisterRubyObj";
%freefunc FXQuatd "HinUnregisterRubyObj";
%freefunc FXQuatf "HinUnregisterRubyObj";
%freefunc FXRanged "HinUnregisterRubyObj";
%freefunc FXRangef "HinUnregisterRubyObj";
%freefunc FXRectangle "HinUnregisterRubyObj";
%freefunc FXRegion "HinUnregisterRubyObj";
%freefunc FXSize "HinUnregisterRubyObj";
%freefunc FXSphered "HinUnregisterRubyObj";
%freefunc FXSpheref "HinUnregisterRubyObj";
%freefunc FXStream "HinUnregisterRubyObj";
// %freefunc FXTablePos "HinUnregisterRubyObj";
// %freefunc FXTableRange "HinUnregisterRubyObj";
%freefunc FXTimer "HinUnregisterRubyObj";
%freefunc FXVec2d "HinUnregisterRubyObj";
%freefunc FXVec2f "HinUnregisterRubyObj";
%freefunc FXVec3d "HinUnregisterRubyObj";
%freefunc FXVec3f "HinUnregisterRubyObj";
%freefunc FXVec4d "HinUnregisterRubyObj";
%freefunc FXVec4f "HinUnregisterRubyObj";
%freefunc FXViewport "HinUnregisterRubyObj";
%freefunc NotifyHeader "HinUnregisterRubyObj";
%freefunc SCNotification "HinUnregisterRubyObj";
