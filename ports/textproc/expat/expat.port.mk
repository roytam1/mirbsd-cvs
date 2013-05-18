# $MirOS: ports/textproc/expat/expat.port.mk,v 1.3 2008/04/07 18:56:22 tg Exp $
# $OpenBSD: iconv.port.mk,v 1.4 2001/11/27 17:44:04 brad Exp $

# This is equivalent to USE_MOTIF.
# Can be one of 'any', 'base', 'X11', 'port'
USE_EXPAT?=	any

.if ${USE_EXPAT:L} == "any"
.  if ${OStype} == "MirBSD"
.    if ${OSver:R} < 8
USE_EXPAT=	port
.    elif ${OSver:R} == 8
USE_EXPAT=	base
.    else
USE_EXPAT=	base
.    endif
.  elif ${OStype} == "Darwin"
USE_EXPAT=	X11
.  elif ${OStype} == "OpenBSD"
USE_EXPAT=	X11
.  else
USE_EXPAT=	port
.  endif
.endif

.if ${USE_EXPAT:L} == "port"
LIB_DEPENDS+=	../pkgview/expat/lib/expat:expat->=2.0.0-1:textproc/expat
EXPAT_PREFIX=	${LOCALBASE}/pkgview/expat
CPPFLAGS+=	-I${EXPAT_PREFIX:Q}/include
LDFLAGS+=	-Wl,-rpath,${EXPAT_PREFIX:Q}/lib -L${EXPAT_PREFIX:Q}/lib
.elif ${USE_EXPAT:L} == "base"
EXPAT_PREFIX=	/usr
.elif ${USE_EXPAT:L} == "x11"
EXPAT_PREFIX=	${X11BASE}
USE_X11=	Yes		# XXX too late in a MODULES file
.else
.  error USE_EXPAT=${USE_EXPAT:L} invalid
.endif
