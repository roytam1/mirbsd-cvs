# $MirOS: src/lib/libpng/Makefile,v 1.6 2007/05/08 21:52:54 tg Exp $

SHLIB_VERSION?= 7.1
LIB=		png
SRCS=		png.c pngerror.c pngget.c pngmem.c pngpread.c \
		pngread.c pngrio.c pngrtran.c pngrutil.c pngset.c \
		pngtrans.c pngwio.c pngwrite.c pngwtran.c pngwutil.c
DPADD+=		${LIBM} ${LIBZ}
LDADD+=		-lm -lz
MAN=		libpng.3 libpngpf.3 png.5
HDRS=		png.h pngconf.h

.include <bsd.own.mk>
COPTS+=		-Wall
CPPFLAGS+=	-DPNG_NO_ASSEMBLER_CODE -DZCONST=const

.include <bsd.lib.mk>
