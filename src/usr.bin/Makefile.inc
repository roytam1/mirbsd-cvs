# $MirOS: src/usr.bin/Makefile.inc,v 1.2 2005/03/13 18:32:40 tg Exp $
# $OpenBSD: Makefile.inc,v 1.2 1996/06/26 05:31:08 deraadt Exp $

.ifndef _MODSRC_USR_BIN_MAKEFILE_INC
_MODSRC_USR_BIN_MAKEFILE_INC=1

BINDIR?=	/usr/bin
LDFLAGS+=	-Wl,-rpath -Wl,/usr/lib

.endif
