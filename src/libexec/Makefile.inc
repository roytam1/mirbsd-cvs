# $MirOS$
# $OpenBSD: Makefile.inc,v 1.2 2001/01/28 19:34:26 niklas Exp $

.ifndef _MODSRC_LIBEXEC_MAKEFILE_INC
_MODSRC_LIBEXEC_MAKEFILE_INC=1

BINDIR?=	/usr/libexec

.if !defined(EXPERIMENTAL)
CFLAGS+=	-Werror
.endif

.endif
