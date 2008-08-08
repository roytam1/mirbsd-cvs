# $MirOS$

LIB=		amxTime
SRCS+=		amxtime.c amx.c

SHLIB_VERSION=	-
SHLIB_SONAME=	lib${LIB}.so
DPADD+=		${.CURDIR}/${LIB}.exp
LDFLAGS+=	-Wl,--version-script,${.CURDIR}/${LIB}.exp

.include <bsd.lib.mk>
