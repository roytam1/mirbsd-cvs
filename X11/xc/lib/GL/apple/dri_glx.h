/**************************************************************************

Copyright 1998-1999 Precision Insight, Inc., Cedar Park, Texas.
Copyright (c) 2002 Apple Computer, Inc.
All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sub license, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice (including the
next paragraph) shall be included in all copies or substantial portions
of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
IN NO EVENT SHALL PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR
ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

**************************************************************************/
/* $XFree86: xc/lib/GL/apple/dri_glx.h,v 1.4 2004/12/10 17:47:24 alanh Exp $ */

/*
 * Authors:
 *   Kevin E. Martin <kevin@precisioninsight.com>
 *   Brian Paul <brian@precisioninsight.com>
 *
 */

#ifndef _DRI_GLX_H_
#define _DRI_GLX_H_

#ifdef GLX_DIRECT_RENDERING

struct __DRIdisplayPrivateRec {
    /*
    ** XFree86-DRI version information
    */
    int driMajor;
    int driMinor;
    int driPatch;

    /*
    ** Array of library handles [indexed by screen number]
    */
    void **libraryHandles;
};

typedef struct __DRIdisplayPrivateRec  __DRIdisplayPrivate;
typedef struct __DRIscreenPrivateRec   __DRIscreenPrivate;
typedef struct __DRIvisualPrivateRec   __DRIvisualPrivate;
typedef struct __DRIcontextPrivateRec  __DRIcontextPrivate;
typedef struct __DRIdrawablePrivateRec __DRIdrawablePrivate;

extern void *__driCreateScreen (Display *dpy, int scrn, __DRIscreen *psc,
				int numConfigs, __GLXvisualConfig *config);
extern void __driRegisterExtensions (void);

#endif /* GLX_DIRECT_RENDERING */
#endif /* _DRI_GLX_H_ */
