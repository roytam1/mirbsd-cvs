# $MirOS$

LIB=		pawnc
SRCS+=		sc1.c sc2.c sc3.c sc4.c sc5.c sc6.c sc7.c \
		scexpand.c sci18n.c sclist.c scmemfil.c scstate.c scvars.c \
		lstring.c memfile.c library.c

CFLAGS_sc1.o=	-DNO_MAIN

SHLIB_VERSION=	0.0
DPADD+=		${.CURDIR}/${LIB}.exp
LDFLAGS+=	-Wl,--version-script,${.CURDIR}/${LIB}.exp

.include <bsd.lib.mk>
