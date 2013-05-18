/* $XFree86: xc/lib/GL/glx/clientattrib.c,v 1.7 2004/04/08 10:07:33 alanh Exp $ */
/*
** License Applicability. Except to the extent portions of this file are
** made subject to an alternative license as permitted in the SGI Free
** Software License B, Version 1.1 (the "License"), the contents of this
** file are subject only to the provisions of the License. You may not use
** this file except in compliance with the License. You may obtain a copy
** of the License at Silicon Graphics, Inc., attn: Legal Services, 1600
** Amphitheatre Parkway, Mountain View, CA 94043-1351, or at:
** 
** http://oss.sgi.com/projects/FreeB
** 
** Note that, as provided in the License, the Software is distributed on an
** "AS IS" basis, with ALL EXPRESS AND IMPLIED WARRANTIES AND CONDITIONS
** DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY IMPLIED WARRANTIES AND
** CONDITIONS OF MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A
** PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
** 
** Original Code. The Original Code is: OpenGL Sample Implementation,
** Version 1.2.1, released January 26, 2000, developed by Silicon Graphics,
** Inc. The Original Code is Copyright (c) 1991-2000 Silicon Graphics, Inc.
** Copyright in any portions created by third parties is as indicated
** elsewhere herein. All Rights Reserved.
** 
** Additional Notice Provisions: The application programming interfaces
** established by SGI in conjunction with the Original Code are The
** OpenGL(R) Graphics System: A Specification (Version 1.2.1), released
** April 1, 1999; The OpenGL(R) Graphics System Utility Library (Version
** 1.3), released November 4, 1998; and OpenGL(R) Graphics with the X
** Window System(R) (Version 1.3), released October 19, 1998. This software
** was created using the OpenGL(R) version 1.2.1 Sample Implementation
** published by SGI, but has not been independently verified as being
** compliant with the OpenGL(R) version 1.2.1 Specification.
**
*/

#include <assert.h>
#define NEED_GL_FUNCS_WRAPPED
#include "glxclient.h"

/*****************************************************************************/

void glEnableClientState(GLenum array)
{
    __GLXcontext *gc = __glXGetCurrentContext();
    __GLXattribute * state = (__GLXattribute *)(gc->client_state_private);

    switch (array) {
	case GL_COLOR_ARRAY:
	    ENABLE_ARRAY(state, color);
	    break;
	case GL_EDGE_FLAG_ARRAY:
	    ENABLE_ARRAY(state, edgeFlag);
	    break;
	case GL_INDEX_ARRAY:
	    ENABLE_ARRAY(state, index);
	    break;
	case GL_NORMAL_ARRAY:
	    ENABLE_ARRAY(state, normal);
	    break;
	case GL_TEXTURE_COORD_ARRAY:
	    ENABLE_TEXARRAY(state, state->vertArray.activeTexture);
	    break;
	case GL_VERTEX_ARRAY:
	    ENABLE_ARRAY(state, vertex);
	    break;
	case GL_SECONDARY_COLOR_ARRAY:
	    ENABLE_ARRAY(state, secondaryColor);
	    break;
	case GL_FOG_COORD_ARRAY:
	    ENABLE_ARRAY(state, fogCoord);
	    break;
	default:
	    __glXSetError(gc, GL_INVALID_ENUM);
    }
}

void glDisableClientState(GLenum array)
{
    __GLXcontext *gc = __glXGetCurrentContext();
    __GLXattribute * state = (__GLXattribute *)(gc->client_state_private);

    switch (array) {
	case GL_COLOR_ARRAY:
	    DISABLE_ARRAY(state, color);
	    break;
	case GL_EDGE_FLAG_ARRAY:
	    DISABLE_ARRAY(state, edgeFlag);
	    break;
	case GL_INDEX_ARRAY:
	    DISABLE_ARRAY(state, index);
	    break;
	case GL_NORMAL_ARRAY:
	    DISABLE_ARRAY(state, normal);
	    break;
	case GL_TEXTURE_COORD_ARRAY:
	    DISABLE_TEXARRAY(state, state->vertArray.activeTexture);
	    break;
	case GL_VERTEX_ARRAY:
	    DISABLE_ARRAY(state, vertex);
	    break;
	case GL_SECONDARY_COLOR_ARRAY:
	    DISABLE_ARRAY(state, secondaryColor);
	    break;
	case GL_FOG_COORD_ARRAY:
	    DISABLE_ARRAY(state, fogCoord);
	    break;
	default:
	    __glXSetError(gc, GL_INVALID_ENUM);
    }
}

/************************************************************************/

void glPushClientAttrib(GLuint mask)
{
    __GLXcontext *gc = __glXGetCurrentContext();
    __GLXattribute * state = (__GLXattribute *)(gc->client_state_private);
    __GLXattribute **spp = gc->attributes.stackPointer, *sp;

    if (spp < &gc->attributes.stack[__GL_CLIENT_ATTRIB_STACK_DEPTH]) {
	if (!(sp = *spp)) {
	    sp = (__GLXattribute *)Xmalloc(sizeof(__GLXattribute));
	    *spp = sp;
	}
	sp->mask = mask;
	gc->attributes.stackPointer = spp + 1;
	if (mask & GL_CLIENT_PIXEL_STORE_BIT) {
	    sp->storePack = state->storePack;
	    sp->storeUnpack = state->storeUnpack;
	}
	if (mask & GL_CLIENT_VERTEX_ARRAY_BIT) {
	    sp->vertArray = state->vertArray;
	}
    } else {
	__glXSetError(gc, GL_STACK_OVERFLOW);
	return;
    }
}

void glPopClientAttrib(void)
{
    __GLXcontext *gc = __glXGetCurrentContext();
    __GLXattribute * state = (__GLXattribute *)(gc->client_state_private);
    __GLXattribute **spp = gc->attributes.stackPointer, *sp;
    GLuint mask;

    if (spp > &gc->attributes.stack[0]) {
	--spp;
	sp = *spp;
	assert(sp != 0);
	mask = sp->mask;
	gc->attributes.stackPointer = spp;

	if (mask & GL_CLIENT_PIXEL_STORE_BIT) {
	    state->storePack = sp->storePack;
	    state->storeUnpack = sp->storeUnpack;
	}
	if (mask & GL_CLIENT_VERTEX_ARRAY_BIT) {
	    state->vertArray = sp->vertArray;
	}

	sp->mask = 0;
    } else {
	__glXSetError(gc, GL_STACK_UNDERFLOW);
	return;
    }
}

void __glFreeAttributeState(__GLXcontext *gc)
{
    __GLXattribute *sp, **spp;

    for (spp = &gc->attributes.stack[0];
         spp < &gc->attributes.stack[__GL_CLIENT_ATTRIB_STACK_DEPTH];
	 spp++) {
	sp = *spp;
        if (sp) {
            XFree((char *)sp);
        } else {
            break;
	}
    }
}


