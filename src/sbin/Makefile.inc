# $MirOS: src/sbin/Makefile.inc,v 1.5 2008/03/27 14:53:23 tg Exp $
# $OpenBSD: Makefile.inc,v 1.4 1997/09/21 11:36:00 deraadt Exp $

.ifndef _MODSRC_SBIN_MAKEFILE_INC
_MODSRC_SBIN_MAKEFILE_INC=1

BINDIR?=	/usr/dsbin
LDFLAGS+=	-Wl,-rpath -Wl,/usr/lib

.endif
