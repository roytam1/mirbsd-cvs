# $MirOS: ports/lang/pawn/toolkit/files/amx/amxString/Makefile,v 1.1.1.1 2008/08/08 15:53:57 tg Exp $

LIB=		amxString
SRCS+=		amxstring.c amx.c

SHLIB_VERSION=	-
SHLIB_SONAME=	${LIB}.so
DPADD+=		${.CURDIR}/${LIB}.exp
LDFLAGS+=	-Wl,--version-script,${.CURDIR}/${LIB}.exp

NEED_AMXCONS=	Yes

.include <bsd.lib.mk>
