# $MirOS: src/libexec/Makefile.inc,v 1.3 2005/03/06 21:48:04 tg Exp $
# $OpenBSD: Makefile.inc,v 1.2 2001/01/28 19:34:26 niklas Exp $

.ifndef _MODSRC_LIBEXEC_MAKEFILE_INC
_MODSRC_LIBEXEC_MAKEFILE_INC=1

BINDIR?=	/usr/libexec
LDFLAGS+=	-Wl,-rpath -Wl,/usr/lib

.endif
