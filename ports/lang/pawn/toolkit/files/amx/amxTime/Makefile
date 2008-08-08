# $MirOS: ports/lang/pawn/toolkit/files/amx/amxTime/Makefile,v 1.1.1.1 2008/08/08 15:53:57 tg Exp $

LIB=		amxTime
SRCS+=		amxtime.c amx.c

SHLIB_VERSION=	-
SHLIB_SONAME=	${LIB}.so
DPADD+=		${.CURDIR}/${LIB}.exp
LDFLAGS+=	-Wl,--version-script,${.CURDIR}/${LIB}.exp

.include <bsd.lib.mk>
