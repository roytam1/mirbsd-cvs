# $MirOS: src/bin/Makefile.inc,v 1.6 2008/03/27 15:00:43 tg Exp $
# $OpenBSD: Makefile.inc,v 1.4 1997/09/21 11:34:33 deraadt Exp $

.ifndef _MODSRC_BIN_MAKEFILE_INC
_MODSRC_BIN_MAKEFILE_INC=1

BINDIR?=	/bin
LDFLAGS+=	-Wl,-rpath -Wl,/usr/lib

.endif
