/* $XFree86: xc/programs/Xserver/hw/xfree86/loader/fontsym.c,v 1.16 2004/09/15 15:01:26 dawes Exp $ */
/*
 * Copyright (c) 1998-2004 by The XFree86 Project, Inc.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 *   1.  Redistributions of source code must retain the above copyright
 *       notice, this list of conditions, and the following disclaimer.
 *
 *   2.  Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer
 *       in the documentation and/or other materials provided with the
 *       distribution, and in the same place and form as other copyright,
 *       license and disclaimer information.
 *
 *   3.  The end-user documentation included with the redistribution,
 *       if any, must include the following acknowledgment: "This product
 *       includes software developed by The XFree86 Project, Inc
 *       (http://www.xfree86.org/) and its contributors", in the same
 *       place and form as other third-party acknowledgments.  Alternately,
 *       this acknowledgment may appear in the software itself, in the
 *       same form and location as other such third-party acknowledgments.
 *
 *   4.  Except as contained in this notice, the name of The XFree86
 *       Project, Inc shall not be used in advertising or otherwise to
 *       promote the sale, use or other dealings in this Software without
 *       prior written authorization from The XFree86 Project, Inc.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE XFREE86 PROJECT, INC OR ITS CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "font.h"
#include "sym.h"
#include "fntfilst.h"
#include "fontenc.h"
#ifdef FONTENC_COMPATIBILITY
#include "fontencc.h"
#endif
#include "fntfilio.h"
#include "fntfil.h"
#include "fontutil.h"
#include "fontxlfd.h"
#ifdef FONTCACHE
#define _FONTCACHE_SERVER_
#include "fontcache.h"
#endif

LOOKUP fontLookupTab[] = {

    SYMFUNC(TwoByteSwap)
    SYMFUNC(FourByteSwap)
    SYMFUNC(FontCouldBeTerminal)
    SYMFUNC(BufFileRead)
    SYMFUNC(BufFileWrite)
    SYMFUNC(CheckFSFormat)
    SYMFUNC(FontFileOpen)
    SYMFUNC(FontFilePriorityRegisterRenderer)
    SYMFUNC(FontFileRegisterRenderer)
    SYMFUNC(FontParseXLFDName)
    SYMFUNC(FontFileCloseFont)
    SYMFUNC(FontFileOpenBitmap)
    SYMFUNC(FontFileCompleteXLFD)
    SYMFUNC(FontFileCountDashes)
    SYMFUNC(FontFileFindNameInDir)
    SYMFUNC(FontFileClose)
    SYMFUNC(FontComputeInfoAccelerators)
    SYMFUNC(FontDefaultFormat)
    SYMFUNC(NameForAtom)
    SYMFUNC(BitOrderInvert)
    SYMFUNC(FontFileMatchRenderer)
    SYMFUNC(RepadBitmap)
    SYMFUNC(FontEncName)
    SYMFUNC(FontEncRecode)
    SYMFUNC(FontEncFind)
    SYMFUNC(FontMapFind)
    SYMFUNC(FontEncMapFind)
    SYMFUNC(FontEncFromXLFD)
    SYMFUNC(FontEncDirectory)
    SYMFUNC(FontMapReverse)
    SYMFUNC(FontMapReverseFree)
    SYMFUNC(CreateFontRec)
    SYMFUNC(DestroyFontRec)
    SYMFUNC(GetGlyphs)
    SYMFUNC(QueryGlyphExtents)
    SYMFUNC(AllocateFontPrivateIndex)

    SYMVAR(FontFileBitmapSources)

#ifdef FONTENC_COMPATIBILITY
    /* Obsolete backwards compatibility symbols -- fontencc.c */
    SYMFUNC(font_encoding_from_xlfd)
    SYMFUNC(font_encoding_find)
    SYMFUNC(font_encoding_recode)
    SYMFUNC(font_encoding_name)
    SYMFUNC(identifyEncodingFile)
#endif

#ifdef FONTCACHE
    /* fontcache.c */
    SYMFUNC(FontCacheGetSettings)
    SYMFUNC(FontCacheGetStatistics)
    SYMFUNC(FontCacheChangeSettings)
    SYMFUNC(FontCacheOpenCache)
    SYMFUNC(FontCacheCloseCache)
    SYMFUNC(FontCacheSearchEntry)
    SYMFUNC(FontCacheGetEntry)
    SYMFUNC(FontCacheInsertEntry)
    SYMFUNC(FontCacheGetBitmap)
#endif

    {0, 0}
};
