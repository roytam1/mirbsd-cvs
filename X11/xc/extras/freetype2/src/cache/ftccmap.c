/***************************************************************************/
/*                                                                         */
/*  ftccmap.c                                                              */
/*                                                                         */
/*    FreeType CharMap cache (body)                                        */
/*                                                                         */
/*  Copyright 2000-2001, 2002, 2003, 2004 by                               */
/*  David Turner, Robert Wilhelm, and Werner Lemberg.                      */
/*                                                                         */
/*  This file is part of the FreeType project, and may only be used,       */
/*  modified, and distributed under the terms of the FreeType project      */
/*  license, LICENSE.TXT.  By continuing to use, modify, or distribute     */
/*  this file you indicate that you have read the license and              */
/*  understand and accept it fully.                                        */
/*                                                                         */
/***************************************************************************/


#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_CACHE_H
#include FT_CACHE_INTERNAL_MANAGER_H
#include FT_INTERNAL_MEMORY_H
#include FT_INTERNAL_DEBUG_H
#include FT_TRUETYPE_IDS_H

#include "ftccback.h"
#include "ftcerror.h"

#undef  FT_COMPONENT
#define FT_COMPONENT  trace_cache


  /*************************************************************************/
  /*                                                                       */
  /* Each FTC_CMapNode contains a simple array to map a range of character */
  /* codes to equivalent glyph indices.                                    */
  /*                                                                       */
  /* For now, the implementation is very basic: Each node maps a range of  */
  /* 128 consecutive character codes to their corresponding glyph indices. */
  /*                                                                       */
  /* We could do more complex things, but I don't think it is really very  */
  /* useful.                                                               */
  /*                                                                       */
  /*************************************************************************/


  /* number of glyph indices / character code per node */
#define FTC_CMAP_INDICES_MAX  128

  /* compute a query/node hash */
#define FTC_CMAP_HASH( faceid, index, charcode )           \
          ( FTC_FACE_ID_HASH( faceid ) + 211 * ( index ) + \
            ( (char_code) / FTC_CMAP_INDICES_MAX )       )

  /* the charmap query */
  typedef struct  FTC_CMapQueryRec_
  {
    FTC_FaceID  face_id;
    FT_UInt     cmap_index;
    FT_UInt32   char_code;

  } FTC_CMapQueryRec, *FTC_CMapQuery;

#define FTC_CMAP_QUERY( x )  ((FTC_CMapQuery)(x))
#define FTC_CMAP_QUERY_HASH( x )                                         \
          FTC_CMAP_HASH( (x)->face_id, (x)->cmap_index, (x)->char_code )

  /* the cmap cache node */
  typedef struct  FTC_CMapNodeRec_
  {
    FTC_NodeRec  node;
    FTC_FaceID   face_id;
    FT_UInt      cmap_index;
    FT_UInt32    first;                         /* first character in node */
    FT_UInt16    indices[FTC_CMAP_INDICES_MAX]; /* array of glyph indices  */

  } FTC_CMapNodeRec, *FTC_CMapNode;

#define FTC_CMAP_NODE( x ) ( (FTC_CMapNode)( x ) )
#define FTC_CMAP_NODE_HASH( x )                                      \
          FTC_CMAP_HASH( (x)->face_id, (x)->cmap_index, (x)->first )

  /* if (indices[n] == FTC_CMAP_UNKNOWN), we assume that the corresponding */
  /* glyph indices haven't been queried through FT_Get_Glyph_Index() yet   */
#define FTC_CMAP_UNKNOWN  ( (FT_UInt16)-1 )


  /*************************************************************************/
  /*************************************************************************/
  /*****                                                               *****/
  /*****                        CHARMAP NODES                          *****/
  /*****                                                               *****/
  /*************************************************************************/
  /*************************************************************************/


  /* no need for specific finalizer; we use `ftc_node_done' directly */

  FT_CALLBACK_DEF( void )
  ftc_cmap_node_free( FTC_CMapNode  node,
                      FTC_Cache     cache )
  {
    FT_Memory  memory = cache->memory;


    FT_FREE( node );
  }


  /* initialize a new cmap node */
  FT_CALLBACK_DEF( FT_Error )
  ftc_cmap_node_new( FTC_CMapNode  *anode,
                     FTC_CMapQuery  query,
                     FTC_Cache      cache )
  {
    FT_Error      error;
    FT_Memory     memory  = cache->memory;
    FTC_CMapNode  node;
    FT_UInt       nn;


    if ( !FT_NEW( node ) )
    {
      node->face_id    = query->face_id;
      node->cmap_index = query->cmap_index;
      node->first      = (query->char_code / FTC_CMAP_INDICES_MAX) *
                         FTC_CMAP_INDICES_MAX;

      for ( nn = 0; nn < FTC_CMAP_INDICES_MAX; nn++ )
        node->indices[nn] = FTC_CMAP_UNKNOWN;
    }

    *anode = node;
    return error;
  }


  /* compute the weight of a given cmap node */
  FT_CALLBACK_DEF( FT_ULong )
  ftc_cmap_node_weight( FTC_CMapNode  cnode )
  {
    FT_UNUSED( cnode );

    return sizeof ( *cnode );
  }


  /* compare a cmap node to a given query */
  FT_CALLBACK_DEF( FT_Bool )
  ftc_cmap_node_compare( FTC_CMapNode   node,
                         FTC_CMapQuery  query )
  {
    if ( node->face_id    == query->face_id    &&
         node->cmap_index == query->cmap_index )
    {
      FT_UInt32  offset = (FT_UInt32)( query->char_code - node->first );


      return FT_BOOL( offset < FTC_CMAP_INDICES_MAX );
    }

    return 0;
  }


  FT_CALLBACK_DEF( FT_Bool )
  ftc_cmap_node_remove_faceid( FTC_CMapNode  node,
                               FTC_FaceID    face_id )
  {
    return FT_BOOL( node->face_id == face_id );
  }


  /*************************************************************************/
  /*************************************************************************/
  /*****                                                               *****/
  /*****                    GLYPH IMAGE CACHE                          *****/
  /*****                                                               *****/
  /*************************************************************************/
  /*************************************************************************/


  FT_CALLBACK_TABLE_DEF
  const FTC_CacheClassRec  ftc_cmap_cache_class =
  {
    (FTC_Node_NewFunc)    ftc_cmap_node_new,
    (FTC_Node_WeightFunc) ftc_cmap_node_weight,
    (FTC_Node_CompareFunc)ftc_cmap_node_compare,
    (FTC_Node_CompareFunc)ftc_cmap_node_remove_faceid,
    (FTC_Node_FreeFunc)   ftc_cmap_node_free,

    sizeof ( FTC_CacheRec ),
    (FTC_Cache_InitFunc)  ftc_cache_init,
    (FTC_Cache_DoneFunc)  ftc_cache_done,
  };


  /* documentation is in ftccmap.h */

  FT_EXPORT_DEF( FT_Error )
  FTC_CMapCache_New( FTC_Manager     manager,
                     FTC_CMapCache  *acache )
  {
    return FTC_Manager_RegisterCache( manager,
                                      &ftc_cmap_cache_class,
                                      FTC_CACHE_P( acache ) );
  }


  /* documentation is in ftccmap.h */

  FT_EXPORT_DEF( FT_UInt )
  FTC_CMapCache_Lookup( FTC_CMapCache  cmap_cache,
                        FTC_FaceID     face_id,
                        FT_Int         cmap_index,
                        FT_UInt32      char_code )
  {
    FTC_Cache         cache = FTC_CACHE( cmap_cache );
    FTC_CMapQueryRec  query;
    FTC_CMapNode      node;
    FT_Error          error;
    FT_UInt           gindex = 0;
    FT_UInt32         hash;


    if ( !cache )
    {
      FT_ERROR(( "FTC_CMapCache_Lookup: bad arguments, returning 0!\n" ));
      return 0;
    }

    query.face_id    = face_id;
    query.cmap_index = (FT_UInt)cmap_index;
    query.char_code  = char_code;

    hash = FTC_CMAP_HASH( face_id, cmap_index, char_code );

#if 1
    FTC_CACHE_LOOKUP_CMP( cache, ftc_cmap_node_compare, hash, &query,
                          node, error );
#else
    error = FTC_Cache_Lookup( cache, hash, &query, (FTC_Node*) &node );
#endif
    if ( error )
      goto Exit;

    FT_ASSERT( (FT_UInt)( char_code - node->first ) < FTC_CMAP_INDICES_MAX );

    gindex = node->indices[char_code - node->first];
    if ( gindex == FTC_CMAP_UNKNOWN )
    {
      FT_Face  face;


      gindex = 0;

      error = FTC_Manager_LookupFace( cache->manager, node->face_id, &face );
      if ( error )
        goto Exit;

      if ( (FT_UInt)cmap_index < (FT_UInt)face->num_charmaps )
      {
        FT_CharMap  old, cmap  = NULL;


        old  = face->charmap;
        cmap = face->charmaps[cmap_index];

        if ( old != cmap )
          FT_Set_Charmap( face, cmap );

        gindex = FT_Get_Char_Index( face, char_code );

        if ( old != cmap )
          FT_Set_Charmap( face, old );
      }

      node->indices[char_code - node->first] = gindex;
    }

  Exit:
    return gindex;
  }


/* END */
