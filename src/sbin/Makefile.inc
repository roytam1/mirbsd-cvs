# $MirOS: src/sbin/Makefile.inc,v 1.7 2009/03/29 13:04:20 tg Exp $
# $OpenBSD: Makefile.inc,v 1.4 1997/09/21 11:36:00 deraadt Exp $

.ifndef _MODSRC_SBIN_MAKEFILE_INC
_MODSRC_SBIN_MAKEFILE_INC=1

BINDIR?=	/sbin
LDFLAGS+=	-Wl,-rpath -Wl,/usr/lib
LDSTATIC=	-static

.endif
