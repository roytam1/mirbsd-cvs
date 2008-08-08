# $MirOS$

LIB=		amxProcess
SRCS+=		amxprocess.c amx.c

SHLIB_VERSION=	-
SHLIB_SONAME=	lib${LIB}.so
DPADD+=		${.CURDIR}/${LIB}.exp
LDFLAGS+=	-Wl,--version-script,${.CURDIR}/${LIB}.exp

DPADD+=		${LIBDL}
LDADD+=		-ldl -lffi

.include <bsd.lib.mk>
