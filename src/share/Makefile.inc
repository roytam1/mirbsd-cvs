# $MirOS$
# $OpenBSD: Makefile.inc,v 1.2 2001/02/03 08:25:16 niklas Exp $

.ifndef _MODSRC_SHARE_MAKEFILE_INC
_MODSRC_SHARE_MAKEFILE_INC=1

BINDIR?=	/usr/share

.if !defined(EXPERIMENTAL)
CFLAGS+=	-Werror
.endif

.endif
