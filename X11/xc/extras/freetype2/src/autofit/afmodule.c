#include "afmodule.h"
#include "afloader.h"
#include FT_INTERNAL_OBJECTS_H

  typedef struct  FT_AutofitterRec_
  {
    FT_ModuleRec  root;
    AF_LoaderRec  loader[1];

  } FT_AutofitterRec, *FT_Autofitter;


  FT_CALLBACK_DEF( FT_Error )
  af_autofitter_init( FT_Autofitter  module )
  {
    return af_loader_init( module->loader, module->root.library->memory );
  }


  FT_CALLBACK_DEF( void )
  af_autofitter_done( FT_Autofitter  module )
  {
    af_loader_done( module->loader );
  }


  FT_CALLBACK_DEF( FT_Error )
  af_autofitter_load_glyph( FT_Autofitter  module,
                            FT_GlyphSlot   slot,
                            FT_Size        size,
                            FT_UInt        glyph_index,
                            FT_Int32       load_flags )
  {
    FT_UNUSED(size);

    return af_loader_load_glyph( module->loader, slot->face,
                                 glyph_index, load_flags );
  }



  FT_CALLBACK_TABLE_DEF
  const FT_AutoHinter_ServiceRec  af_autofitter_service =
  {
    NULL,
    NULL,
    NULL,
    (FT_AutoHinter_GlyphLoadFunc) af_autofitter_load_glyph
  };


  FT_CALLBACK_TABLE_DEF
  const FT_Module_Class  autofit_module_class =
  {
    FT_MODULE_HINTER,
    sizeof ( FT_AutofitterRec ),

    "autofitter",
    0x10000L,   /* version 1.0 of the autofitter  */
    0x20000L,   /* requires FreeType 2.0 or above */

    (const void*) &af_autofitter_service,

    (FT_Module_Constructor) af_autofitter_init,
    (FT_Module_Destructor)  af_autofitter_done,
    (FT_Module_Requester)   0
  };


/* END */
