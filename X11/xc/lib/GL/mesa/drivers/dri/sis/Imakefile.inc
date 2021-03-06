XCOMM $XFree86: xc/lib/GL/mesa/drivers/dri/sis/Imakefile.inc,v 1.4 2005/03/01 03:48:50 dawes Exp $

#ifndef MesaDrvSrcDir
#define MesaDrvSrcDir $(MESASRCDIR)/src/mesa/drivers/dri
#endif

MESADRVSRCDIR = MesaDrvSrcDir

#ifndef MesaDrvSisBuildDir
#define MesaDrvSisBuildDir /**/
#endif
MESADRVSISBUILDDIR = MesaDrvSisBuildDir

#if Malloc0ReturnsNull
ALLOC_DEFINES = -DMALLOC_0_RETURNS_NULL
#endif

#if BuildXF86DRI
  DRI_DEFINES = GlxDefines $(SIS_DEFINES) -DX_BYTE_ORDER=$(X_BYTE_ORDER)
 DRI_INCLUDES = -I$(GLXLIBSRC)/dri \
		-I$(XINCLUDESRC) \
		-I$(GLXLIBSRC)/glx \
		-I$(GLXLIBSRC)/include \
		-I$(SERVERSRC)/GL/dri \
		-I$(XF86OSSRC) \
		-I$(DRMINCLUDESDIR) \
		-I$(XF86DRIVERSRC)/sis \
		-I$(GLXLIBSRC)/dri/drm
#endif

MESA_INCLUDES = -I$(MESASRCDIR)/src/mesa \
		-I$(MESASRCDIR)/src/mesa/main \
		-I$(MESASRCDIR)/src/mesa/glapi \
		-I$(MESASRCDIR)/src/mesa/shader \
		-I$(MESASRCDIR)/include \
		-I$(MESADRVSRCDIR)/common \
		-I$(MESADRVSRCDIR)/sis
   X_INCLUDES = -I$(XINCLUDESRC) -I$(EXTINCSRC)

#if 0
 DEBUG_SRC = $(MESADRVSISBUILDDIR)sis_debug.c
 DEBUG_OBJ = $(MESADRVSISBUILDDIR)sis_debug.o
 DEBUG_EOBJ = $(MESADRVSISBUILDDIR)$(EXTRASUBDIR)/sis_debug.o
 DEBUG_UOBJ = $(MESADRVSISBUILDDIR)unshared/sis_debug.o
 DEBUG_DOBJ = $(MESADRVSISBUILDDIR)debugger/sis_debug.o
 DEBUG_POBJ = $(MESADRVSISBUILDDIR)profiled/sis_debug.o
 DEBUG_DEFINES += -DSIS_DUMP
#ifdef NeedToLinkMesaSrc
LinkSourceFile(sis_debug.c, $(MESADRVSRCDIR)/sis)
#endif
#endif

      SISSRCS = $(MESADRVSISBUILDDIR)sis_alloc.c \
		$(MESADRVSISBUILDDIR)sis_dd.c \
		$(MESADRVSISBUILDDIR)sis_lock.c \
		$(MESADRVSISBUILDDIR)sis_context.c \
		$(MESADRVSISBUILDDIR)sis_fog.c \
		$(MESADRVSISBUILDDIR)sis_clear.c \
		$(MESADRVSISBUILDDIR)sis_screen.c \
		$(MESADRVSISBUILDDIR)sis_state.c \
		$(MESADRVSISBUILDDIR)sis_stencil.c \
		$(MESADRVSISBUILDDIR)sis_span.c \
		$(MESADRVSISBUILDDIR)sis_tex.c \
		$(MESADRVSISBUILDDIR)sis_texstate.c \
		$(MESADRVSISBUILDDIR)sis_tris.c \
		$(DEBUG_SRC)

      SISOBJS = $(MESADRVSISBUILDDIR)sis_alloc.o \
		$(MESADRVSISBUILDDIR)sis_dd.o \
		$(MESADRVSISBUILDDIR)sis_lock.o \
		$(MESADRVSISBUILDDIR)sis_context.o \
		$(MESADRVSISBUILDDIR)sis_fog.o \
		$(MESADRVSISBUILDDIR)sis_clear.o \
		$(MESADRVSISBUILDDIR)sis_screen.o \
		$(MESADRVSISBUILDDIR)sis_state.o \
		$(MESADRVSISBUILDDIR)sis_stencil.o \
		$(MESADRVSISBUILDDIR)sis_span.o \
		$(MESADRVSISBUILDDIR)sis_tex.o \
		$(MESADRVSISBUILDDIR)sis_texstate.o \
		$(MESADRVSISBUILDDIR)sis_tris.o \
		$(DEBUG_OBJ)

      SISEOBJS = $(MESADRVSISBUILDDIR)$(EXTRASUBDIR)/sis_alloc.o \
		$(MESADRVSISBUILDDIR)$(EXTRASUBDIR)/sis_dd.o \
		$(MESADRVSISBUILDDIR)$(EXTRASUBDIR)/sis_lock.o \
		$(MESADRVSISBUILDDIR)$(EXTRASUBDIR)/sis_context.o \
		$(MESADRVSISBUILDDIR)$(EXTRASUBDIR)/sis_fog.o \
		$(MESADRVSISBUILDDIR)$(EXTRASUBDIR)/sis_clear.o \
		$(MESADRVSISBUILDDIR)$(EXTRASUBDIR)/sis_screen.o \
		$(MESADRVSISBUILDDIR)$(EXTRASUBDIR)/sis_state.o \
		$(MESADRVSISBUILDDIR)$(EXTRASUBDIR)/sis_stencil.o \
		$(MESADRVSISBUILDDIR)$(EXTRASUBDIR)/sis_span.o \
		$(MESADRVSISBUILDDIR)$(EXTRASUBDIR)/sis_tex.o \
		$(MESADRVSISBUILDDIR)$(EXTRASUBDIR)/sis_texstate.o \
		$(MESADRVSISBUILDDIR)$(EXTRASUBDIR)/sis_tris.o \
		$(DEBUG_EOBJ)

      SISUOBJS = $(MESADRVSISBUILDDIR)unshared/sis_alloc.o \
		$(MESADRVSISBUILDDIR)unshared/sis_dd.o \
		$(MESADRVSISBUILDDIR)unshared/sis_lock.o \
		$(MESADRVSISBUILDDIR)unshared/sis_context.o \
		$(MESADRVSISBUILDDIR)unshared/sis_fog.o \
		$(MESADRVSISBUILDDIR)unshared/sis_clear.o \
		$(MESADRVSISBUILDDIR)unshared/sis_screen.o \
		$(MESADRVSISBUILDDIR)unshared/sis_state.o \
		$(MESADRVSISBUILDDIR)unshared/sis_stencil.o \
		$(MESADRVSISBUILDDIR)unshared/sis_span.o \
		$(MESADRVSISBUILDDIR)unshared/sis_tex.o \
		$(MESADRVSISBUILDDIR)unshared/sis_texstate.o \
		$(MESADRVSISBUILDDIR)unshared/sis_tris.o \
		$(DEBUG_UOBJ)

      SISDOBJS = $(MESADRVSISBUILDDIR)debugger/sis_alloc.o \
		$(MESADRVSISBUILDDIR)debugger/sis_dd.o \
		$(MESADRVSISBUILDDIR)debugger/sis_lock.o \
		$(MESADRVSISBUILDDIR)debugger/sis_context.o \
		$(MESADRVSISBUILDDIR)debugger/sis_fog.o \
		$(MESADRVSISBUILDDIR)debugger/sis_clear.o \
		$(MESADRVSISBUILDDIR)debugger/sis_screen.o \
		$(MESADRVSISBUILDDIR)debugger/sis_state.o \
		$(MESADRVSISBUILDDIR)debugger/sis_stencil.o \
		$(MESADRVSISBUILDDIR)debugger/sis_span.o \
		$(MESADRVSISBUILDDIR)debugger/sis_tex.o \
		$(MESADRVSISBUILDDIR)debugger/sis_texstate.o \
		$(MESADRVSISBUILDDIR)debugger/sis_tris.o \
		$(DEBUG_DOBJ)

      SISPOBJS = $(MESADRVSISBUILDDIR)profiled/sis_alloc.o \
		$(MESADRVSISBUILDDIR)profiled/sis_dd.o \
		$(MESADRVSISBUILDDIR)profiled/sis_lock.o \
		$(MESADRVSISBUILDDIR)profiled/sis_context.o \
		$(MESADRVSISBUILDDIR)profiled/sis_fog.o \
		$(MESADRVSISBUILDDIR)profiled/sis_clear.o \
		$(MESADRVSISBUILDDIR)profiled/sis_screen.o \
		$(MESADRVSISBUILDDIR)profiled/sis_state.o \
		$(MESADRVSISBUILDDIR)profiled/sis_stencil.o \
		$(MESADRVSISBUILDDIR)profiled/sis_span.o \
		$(MESADRVSISBUILDDIR)profiled/sis_tex.o \
		$(MESADRVSISBUILDDIR)profiled/sis_texstate.o \
		$(MESADRVSISBUILDDIR)profiled/sis_tris.o \
		$(DEBUG_POBJ)

#ifdef NeedToLinkMesaSrc
LinkSourceFile(sis_alloc.c, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_alloc.h, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_common2.h, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_context.h, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_dd.c, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_dd.h, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_debug.c, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_debug.h, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_lock.c, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_lock.h, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_context.c, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_fog.c, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_clear.c, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_reg.h, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_screen.c, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_screen.h, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_state.c, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_state.h, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_stencil.c, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_stencil.h, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_span.c, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_span.h, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_tex.c, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_tex.h, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_texstate.c, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_tris.c, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_tris.h, $(MESADRVSRCDIR)/sis)
LinkSourceFile(sis_tritmp.h, $(MESADRVSRCDIR)/sis)
#endif
