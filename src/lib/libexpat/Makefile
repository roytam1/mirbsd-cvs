# $MirOS: src/lib/libexpat/Makefile,v 1.5 2006/06/01 23:33:35 tg Exp $
# $OpenBSD: Makefile,v 1.2 2004/09/22 21:37:35 espie Exp $

SHLIB_VERSION?= 6.0
LIB=		expat
.PATH: ${.CURDIR}/lib
SRCS=		xmlparse.c xmltok.c xmlrole.c
HDRS=		lib/expat.h lib/expat_external.h

.include <bsd.own.mk>
COPTS+=		-Wall
CPPFLAGS+=	-DHAVE_EXPAT_CONFIG_H

.include <bsd.lib.mk>
