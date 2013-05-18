# $MirOS: src/bin/Makefile.inc,v 1.5 2008/03/27 14:53:22 tg Exp $
# $OpenBSD: Makefile.inc,v 1.4 1997/09/21 11:34:33 deraadt Exp $

.ifndef _MODSRC_BIN_MAKEFILE_INC
_MODSRC_BIN_MAKEFILE_INC=1

BINDIR?=	/usr/dbin
LDFLAGS+=	-Wl,-rpath -Wl,/usr/lib

.endif
