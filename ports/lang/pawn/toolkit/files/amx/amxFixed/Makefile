# $MirOS: ports/lang/pawn/toolkit/files/amx/amxFixed/Makefile,v 1.1.1.1 2008/08/08 15:53:57 tg Exp $

LIB=		amxFixed
SRCS+=		fixed.c amx.c

DPADD+=		${LIBM}
LDADD+=		-lm

SHLIB_VERSION=	-
SHLIB_SONAME=	${LIB}.so
DPADD+=		${.CURDIR}/${LIB}.exp
LDFLAGS+=	-Wl,--version-script,${.CURDIR}/${LIB}.exp

.include <bsd.lib.mk>
