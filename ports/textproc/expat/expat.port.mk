# $MirOS: ports/textproc/expat/expat.port.mk,v 1.1 2006/05/29 21:23:29 bsiegert Exp $
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
LIB_DEPENDS+=	expat::textproc/expat
EXPAT_PREFIX=	${LOCALBASE}
.elif ${USE_EXPAT:L} == "base"
EXPAT_PREFIX=	/usr
.elif ${USE_EXPAT:L} == "x11"
EXPAT_PREFIX=	${X11BASE}
USE_X11=	Yes
.else
.  error USE_EXPAT=${USE_EXPAT:L} invalid
.endif
