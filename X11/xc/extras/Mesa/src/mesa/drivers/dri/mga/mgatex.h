/* $XFree86: xc/extras/Mesa/src/mesa/drivers/dri/mga/mgatex.h,v 1.1.1.2 2004/06/10 14:22:56 alanh Exp $ */
/*
 * Copyright 2000-2001 VA Linux Systems, Inc.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * on the rights to use, copy, modify, merge, publish, distribute, sub
 * license, and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Keith Whitwell <keith@tungstengraphics.com>
 */

#ifndef MGATEX_INC
#define MGATEX_INC

#include "mgacontext.h"

typedef struct mga_texture_object_s *mgaTextureObjectPtr;


/* Called before a primitive is rendered to make sure the texture
 * state is properly setup.  Texture residence is checked later
 * when we grab the lock.
 */
void mgaUpdateTextureState( GLcontext *ctx );

int mgaUploadTexImages( mgaContextPtr mmesa, mgaTextureObjectPtr t );

void mgaDestroyTexObj( mgaContextPtr mmesa, mgaTextureObjectPtr t );

void mgaInitTextureFuncs( struct dd_function_table *functions );

GLboolean mgaUpdateTextureEnvCombine( GLcontext *ctx, int unit );

#endif
