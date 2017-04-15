# $MirOS: src/lib/libpng/Makefile,v 1.15 2013/08/06 18:49:25 tg Exp $

SHLIB_VERSION?= 10.1
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
CPPFLAGS+=	-DPNG_PEDANTIC_WARNINGS
CPPFLAGS+=	-DPNG_DEPRECATED= -DPNG_DEPSTRUCT= -DPNG_PRIVATE=

afterinstall:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${.CURDIR}/libpng.pc ${DESTDIR}/usr/libdata/pkgconfig/

.include <bsd.lib.mk>
