# $MirOS: ports/graphics/png/png.port.mk,v 1.4 2006/11/03 22:06:15 tg Exp $

# Valid choices: any, base, port
USE_PNG?=		any

.if ${USE_PNG:L:Many}
.  if ${OStype} != "MirBSD"
USE_PNG=		port
.  elif exists(/usr/lib/libncursesw.a)
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
