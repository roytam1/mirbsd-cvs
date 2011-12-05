/*
 * Mesa 3-D graphics library
 * Version:  6.1
 *
 * Copyright (C) 1999-2004  Brian Paul   All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Keith Whitwell <keith@tungstengraphics.com>
 */


#include "glheader.h"
#include "colormac.h"
#include "context.h"
#include "macros.h"
#include "imports.h"
#include "mtypes.h"

#include "math/m_xform.h"

#include "t_context.h"
#include "t_pipeline.h"

/* Is there any real benefit seperating texmat from texgen?  It means
 * we need two lots of intermediate storage.  Any changes to
 * _NEW_TEXTURE will invalidate both sets -- it's only on changes to
 * *only* _NEW_TEXTURE_MATRIX that texgen survives but texmat doesn't.
 *
 * However, the seperation of this code from the complex texgen stuff
 * is very appealing.
 */
struct texmat_stage_data {
   GLvector4f texcoord[MAX_TEXTURE_COORD_UNITS];
};

#define TEXMAT_STAGE_DATA(stage) ((struct texmat_stage_data *)stage->privatePtr)

static void check_texmat( GLcontext *ctx, struct tnl_pipeline_stage *stage )
{
   GLuint i;
   stage->active = 0;

   if (ctx->Texture._TexMatEnabled && !ctx->VertexProgram._Enabled) {
      GLuint flags = 0;

      for (i = 0 ; i < ctx->Const.MaxTextureCoordUnits ; i++)
	 if (ctx->Texture._TexMatEnabled & ENABLE_TEXMAT(i))
	    flags |= _TNL_BIT_TEX(i);

      stage->active = 1;
      stage->inputs = flags;
      stage->outputs = flags;
   }
}

static GLboolean run_texmat_stage( GLcontext *ctx,
				   struct tnl_pipeline_stage *stage )
{
   struct texmat_stage_data *store = TEXMAT_STAGE_DATA(stage);
   struct vertex_buffer *VB = &TNL_CONTEXT(ctx)->vb;
   GLuint i;

   /* ENABLE_TEXMAT implies that the texture matrix is not the
    * identity, so we don't have to check that here.
    */
   for (i = 0 ; i < ctx->Const.MaxTextureCoordUnits ; i++)
      if (ctx->Texture._TexMatEnabled & ENABLE_TEXMAT(i)) {
	 if (stage->changed_inputs & _TNL_BIT_TEX(i))
	    (void) TransformRaw( &store->texcoord[i],
                                 ctx->TextureMatrixStack[i].Top,
				 VB->TexCoordPtr[i]);

	 VB->AttribPtr[VERT_ATTRIB_TEX0+i] = 
	    VB->TexCoordPtr[i] = &store->texcoord[i];
      }
   return GL_TRUE;
}


/* Called the first time stage->run() is invoked.
 */
static GLboolean alloc_texmat_data( GLcontext *ctx,
				    struct tnl_pipeline_stage *stage )
{
   struct vertex_buffer *VB = &TNL_CONTEXT(ctx)->vb;
   struct texmat_stage_data *store;
   GLuint i;

   stage->privatePtr = CALLOC(sizeof(*store));
   store = TEXMAT_STAGE_DATA(stage);
   if (!store)
      return GL_FALSE;

   for (i = 0 ; i < ctx->Const.MaxTextureCoordUnits ; i++)
      _mesa_vector4f_alloc( &store->texcoord[i], 0, VB->Size, 32 );

   /* Now run the stage.
    */
   stage->run = run_texmat_stage;
   return stage->run( ctx, stage );
}


static void free_texmat_data( struct tnl_pipeline_stage *stage )
{
   struct texmat_stage_data *store = TEXMAT_STAGE_DATA(stage);
   GLuint i;

   if (store) {
      for (i = 0; i < MAX_TEXTURE_COORD_UNITS; i++)
	 if (store->texcoord[i].data)
	    _mesa_vector4f_free( &store->texcoord[i] );
      FREE( store );
      stage->privatePtr = 0;
   }
}



const struct tnl_pipeline_stage _tnl_texture_transform_stage =
{
   "texture transform",			/* name */
   _NEW_TEXTURE|_NEW_TEXTURE_MATRIX|_NEW_PROGRAM,	/* check_state */
   _NEW_TEXTURE|_NEW_TEXTURE_MATRIX,	/* run_state */
   GL_FALSE,				/* active? */
   0,					/* inputs */
   0,					/* outputs */
   0,					/* changed_inputs */
   NULL,				/* private data */
   free_texmat_data,			/* destructor */
   check_texmat,			/* check */
   alloc_texmat_data,			/* run -- initially set to init */
};
