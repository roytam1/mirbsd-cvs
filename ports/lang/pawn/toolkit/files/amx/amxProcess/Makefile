# $MirOS: ports/lang/pawn/toolkit/files/amx/amxProcess/Makefile,v 1.1.1.1 2008/08/08 15:53:57 tg Exp $

LIB=		amxProcess
SRCS+=		amxprocess.c amx.c

SHLIB_VERSION=	-
SHLIB_SONAME=	${LIB}.so
DPADD+=		${.CURDIR}/${LIB}.exp
LDFLAGS+=	-Wl,--version-script,${.CURDIR}/${LIB}.exp

DPADD+=		${LIBDL}
LDADD+=		-ldl -lffi

.include <bsd.lib.mk>
