# $MirOS: src/usr.sbin/Makefile.inc,v 1.2 2005/03/13 19:16:11 tg Exp $
# $OpenBSD: Makefile.inc,v 1.2 1997/09/21 11:43:04 deraadt Exp $

.ifndef _MODSRC_USR_SBIN_MAKEFILE_INC
_MODSRC_USR_SBIN_MAKEFILE_INC=1

BINDIR?=	/usr/sbin
LDFLAGS+=	-Wl,-rpath -Wl,/usr/lib

.endif
