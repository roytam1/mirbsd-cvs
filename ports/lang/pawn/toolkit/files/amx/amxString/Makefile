# $MirOS$

LIB=		amxString
SRCS+=		amxstring.c amx.c

SHLIB_VERSION=	-
SHLIB_SONAME=	lib${LIB}.so
DPADD+=		${.CURDIR}/${LIB}.exp
LDFLAGS+=	-Wl,--version-script,${.CURDIR}/${LIB}.exp

NEED_AMXCONS=	Yes

.include <bsd.lib.mk>
