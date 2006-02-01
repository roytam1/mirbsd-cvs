# $MirOS$
# $OpenBSD: iconv.port.mk,v 1.4 2001/11/27 17:44:04 brad Exp $

# This is equivalent to USE_MOTIF.
# Can be one of 'any', 'base', 'gnu', 'port'
USE_ICONV?=	any

.if ${USE_ICONV:L} == "any"
.  if ${OStype} == "MirBSD"
.    if ${OSver:R} < 8
USE_ICONV=	port
.    elif ${OSver:R} == 8
.      if ${OSver:E} < 163
USE_ICONV=	port
.      else
USE_ICONV=	base
.      endif
.    else
USE_ICONV=	base
.    endif
.  elif ${OStype} == "Darwin"
USE_ICONV=	base
.  else
USE_ICONV=	port
.  endif
.endif

.if ${USE_ICONV:L} == "gnu"
.  if ${OStype} == "Darwin"
USE_ICONV=	base
.  else
USE_ICONV=	port
.  endif
.endif

.if ${USE_ICONV:L} == "port"
# The RUN_DEPENDS entry is to ensure libiconv is installed. This is
# necessary so that we have charset.alias installed on static archs.
# Typically installed in PREFIX/lib.
LIB_DEPENDS+=	iconv::converters/libiconv
RUN_DEPENDS+=	:libiconv-*:converters/libiconv
ICONV_PREFIX=	${LOCALBASE}
.elif ${USE_ICONV:L} == "base"
ICONV_PREFIX=	/usr
.else
.  error USE_ICONV=${USE_ICONV:L} invalid
.endif
