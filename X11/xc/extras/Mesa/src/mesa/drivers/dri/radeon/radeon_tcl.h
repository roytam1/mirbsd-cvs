/* $XFree86: xc/extras/Mesa/src/mesa/drivers/dri/radeon/radeon_tcl.h,v 1.1.1.1 2004/04/08 09:17:15 alanh Exp $ */
/**************************************************************************

Copyright 2000, 2001 ATI Technologies Inc., Ontario, Canada, and
                     Tungsten Grahpics Inc., Austin, Texas.

All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice (including the
next paragraph) shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

**************************************************************************/

/*
 * Authors:
 *   Keith Whitwell <keith@tungstengraphics.com>
 *
 */

#ifndef __RADEON_TCL_H__
#define __RADEON_TCL_H__

#ifdef GLX_DIRECT_RENDERING

#include "radeon_context.h"

extern void radeonTclPrimitive( GLcontext *ctx, GLenum prim, int hw_prim );
extern void radeonEmitEltPrimitive( GLcontext *ctx, GLuint first, GLuint last,
				    GLuint flags );
extern void radeonEmitPrimitive( GLcontext *ctx, GLuint first, GLuint last,
				 GLuint flags );

extern void radeonTclFallback( GLcontext *ctx, GLuint bit, GLboolean mode );
					      
#define RADEON_TCL_FALLBACK_RASTER            0x1 /* rasterization */
#define RADEON_TCL_FALLBACK_UNFILLED          0x2 /* unfilled tris */
#define RADEON_TCL_FALLBACK_LIGHT_TWOSIDE     0x4 /* twoside tris */
#define RADEON_TCL_FALLBACK_MATERIAL          0x8 /* material in vb */
#define RADEON_TCL_FALLBACK_TEXGEN_0          0x10 /* texgen, unit 0 */
#define RADEON_TCL_FALLBACK_TEXGEN_1          0x20 /* texgen, unit 1 */
#define RADEON_TCL_FALLBACK_TEXGEN_2          0x40 /* texgen, unit 2 */
#define RADEON_TCL_FALLBACK_TCL_DISABLE       0x80 /* user disable */
#define RADEON_TCL_FALLBACK_TEXRECT_0         0x100 /* texture rectangle */
#define RADEON_TCL_FALLBACK_TEXRECT_1         0x200 /* texture rectangle */
#define RADEON_TCL_FALLBACK_TEXRECT_2         0x400 /* texture rectangle */

#define RADEON_MAX_TCL_VERTSIZE (15*4)

#define TCL_FALLBACK( ctx, bit, mode )	radeonTclFallback( ctx, bit, mode )


#endif
#endif
