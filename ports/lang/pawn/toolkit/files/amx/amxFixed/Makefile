# $MirOS$

LIB=		amxFixed
SRCS+=		fixed.c amx.c

DPADD+=		${LIBM}
LDADD+=		-lm

SHLIB_VERSION=	-
SHLIB_SONAME=	lib${LIB}.so
DPADD+=		${.CURDIR}/${LIB}.exp
LDFLAGS+=	-Wl,--version-script,${.CURDIR}/${LIB}.exp

.include <bsd.lib.mk>
