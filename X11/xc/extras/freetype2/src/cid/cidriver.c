/***************************************************************************/
/*                                                                         */
/*  cidriver.c                                                             */
/*                                                                         */
/*    CID driver interface (body).                                         */
/*                                                                         */
/*  Copyright 1996-2001, 2002, 2003 by                                     */
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
#include "cidriver.h"
#include "cidgload.h"
#include FT_INTERNAL_DEBUG_H
#include FT_INTERNAL_STREAM_H

#include "ciderrs.h"

#include FT_SERVICE_POSTSCRIPT_NAME_H
#include FT_SERVICE_XFREE86_NAME_H
#include FT_SERVICE_POSTSCRIPT_INFO_H

  /*************************************************************************/
  /*                                                                       */
  /* The macro FT_COMPONENT is used in trace mode.  It is an implicit      */
  /* parameter of the FT_TRACE() and FT_ERROR() macros, used to print/log  */
  /* messages during execution.                                            */
  /*                                                                       */
#undef  FT_COMPONENT
#define FT_COMPONENT  trace_ciddriver


 /*
  *  POSTSCRIPT NAME SERVICE
  *
  */

  static const char*
  cid_get_postscript_name( CID_Face  face )
  {
    const char*  result = face->cid.cid_font_name;


    if ( result && result[0] == '/' )
      result++;

    return result;
  }


  static const FT_Service_PsFontNameRec  cid_service_ps_name =
  {
    (FT_PsName_GetFunc) cid_get_postscript_name
  };


 /*
  *  POSTSCRIPT INFO SERVICE
  *
  */

  static FT_Error
  cid_ps_get_font_info( FT_Face          face,
                        PS_FontInfoRec*  afont_info )
  {
    *afont_info = ((CID_Face)face)->cid.font_info;
    return 0;
  }


  static const FT_Service_PsInfoRec  cid_service_ps_info =
  {
    (PS_GetFontInfoFunc)  cid_ps_get_font_info,
    (PS_HasGlyphNamesFunc)NULL          /* unsupported with CID fonts */
  };


 /*
  *  SERVICE LIST
  *
  */

  static const FT_ServiceDescRec  cid_services[] =
  {
    { FT_SERVICE_ID_POSTSCRIPT_FONT_NAME, &cid_service_ps_name },
    { FT_SERVICE_ID_XF86_NAME,            FT_XF86_FORMAT_CID },
    { FT_SERVICE_ID_POSTSCRIPT_INFO,      &cid_service_ps_info },
    { NULL, NULL }
  };


  static FT_Module_Interface
  cid_get_interface( FT_Driver         driver,
                     const FT_String*  cid_interface )
  {
    FT_UNUSED( driver );
    FT_UNUSED( cid_interface );

    return ft_service_list_lookup( cid_services, cid_interface );
  }



  FT_CALLBACK_TABLE_DEF
  const FT_Driver_ClassRec  t1cid_driver_class =
  {
    /* first of all, the FT_Module_Class fields */
    {
      FT_MODULE_FONT_DRIVER       |
      FT_MODULE_DRIVER_SCALABLE   |
      FT_MODULE_DRIVER_HAS_HINTER,

      sizeof( FT_DriverRec ),
      "t1cid",   /* module name           */
      0x10000L,  /* version 1.0 of driver */
      0x20000L,  /* requires FreeType 2.0 */

      0,

      (FT_Module_Constructor)cid_driver_init,
      (FT_Module_Destructor) cid_driver_done,
      (FT_Module_Requester)  cid_get_interface
    },

    /* then the other font drivers fields */
    sizeof( CID_FaceRec ),
    sizeof( CID_SizeRec ),
    sizeof( CID_GlyphSlotRec ),

    (FT_Face_InitFunc)       cid_face_init,
    (FT_Face_DoneFunc)       cid_face_done,

    (FT_Size_InitFunc)       cid_size_init,
    (FT_Size_DoneFunc)       cid_size_done,
    (FT_Slot_InitFunc)       cid_slot_init,
    (FT_Slot_DoneFunc)       cid_slot_done,

    (FT_Size_ResetPointsFunc)cid_size_reset,
    (FT_Size_ResetPixelsFunc)cid_size_reset,

    (FT_Slot_LoadFunc)       cid_slot_load_glyph,

    (FT_Face_GetKerningFunc) 0,
    (FT_Face_AttachFunc)     0,

    (FT_Face_GetAdvancesFunc)0,
  };


/* END */
