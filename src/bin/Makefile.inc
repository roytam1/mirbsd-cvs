# $MirOS$
# $OpenBSD: Makefile.inc,v 1.4 1997/09/21 11:34:33 deraadt Exp $

.ifndef _MODSRC_BIN_MAKEFILE_INC
_MODSRC_BIN_MAKEFILE_INC=1

BINDIR?=	/bin
LDSTATIC=	${STATIC}

.if !defined(EXPERIMENTAL)
CFLAGS+=	-Werror
.endif

.endif
