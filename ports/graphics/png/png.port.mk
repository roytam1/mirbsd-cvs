# $MirOS: ports/graphics/png/png.port.mk,v 1.5 2008/03/23 17:04:36 tg Exp $

# Valid choices: any, base, port
USE_PNG?=		any

.if ${USE_PNG:L:Many}
.  if ${OStype} != "MirBSD"
USE_PNG=		port
.  elif exists(/usr/lib/libpng.a)
USE_PNG=		base
.  else
USE_PNG=		port
.  endif
.endif

.if ${USE_PNG:L:Mport}
LIB_DEPENDS+=		png::graphics/png
CPPFLAGS+=		-I${LOCALBASE}/include/libpng
.elif !${USE_PNG:L:Mbase}
.  error USE_PNG=${USE_PNG:L} invalid
.endif
