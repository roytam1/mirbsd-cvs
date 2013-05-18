# $MirOS: src/bin/Makefile.inc,v 1.7 2009/03/29 13:04:10 tg Exp $
# $OpenBSD: Makefile.inc,v 1.4 1997/09/21 11:34:33 deraadt Exp $

.ifndef _MODSRC_BIN_MAKEFILE_INC
_MODSRC_BIN_MAKEFILE_INC=1

BINDIR?=	/bin
LDFLAGS+=	-Wl,-rpath -Wl,/usr/lib
LDSTATIC=	-static

.endif
