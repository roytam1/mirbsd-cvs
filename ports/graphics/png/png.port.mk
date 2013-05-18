# $MirOS: ports/graphics/png/png.port.mk,v 1.9 2008/04/12 20:22:14 tg Exp $

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
MODPNG_DEPENDS=		pkgview/png/lib/png:png->=1.2.26-0:graphics/png
PNG_BASE=		${LOCALBASE}/pkgview/png
CPPFLAGS+=		-I${PNG_BASE:Q}/include
LDFLAGS+=		-Wl,-rpath,${PNG_BASE:Q}/lib -L${PNG_BASE:Q}/lib
.elif ${USE_PNG:L:Mbase}
MODPNG_DEPENDS=		#empty
PNG_BASE=		/usr
.else
.  error USE_PNG=${USE_PNG:L} invalid
.endif

.ifndef MODPNG_INHIBIT
LIB_DEPENDS+=		${MODPNG_DEPENDS}
.endif
