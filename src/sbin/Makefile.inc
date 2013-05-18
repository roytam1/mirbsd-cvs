# $MirOS: src/sbin/Makefile.inc,v 1.6 2008/03/27 15:00:44 tg Exp $
# $OpenBSD: Makefile.inc,v 1.4 1997/09/21 11:36:00 deraadt Exp $

.ifndef _MODSRC_SBIN_MAKEFILE_INC
_MODSRC_SBIN_MAKEFILE_INC=1

BINDIR?=	/sbin
LDFLAGS+=	-Wl,-rpath -Wl,/usr/lib

.endif
