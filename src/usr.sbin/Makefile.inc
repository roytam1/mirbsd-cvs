# $MirOS: src/usr.sbin/Makefile.inc,v 1.3 2008/03/27 15:00:44 tg Exp $
# $OpenBSD: Makefile.inc,v 1.2 1997/09/21 11:43:04 deraadt Exp $

.ifndef _MODSRC_USR_SBIN_MAKEFILE_INC
_MODSRC_USR_SBIN_MAKEFILE_INC=1

BINDIR?=	/usr/sbin
.ifndef DEBIAN
LDFLAGS+=	-Wl,-rpath -Wl,/usr/lib
.endif

.endif
