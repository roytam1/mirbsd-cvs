# $MirOS: src/lib/libpng/Makefile,v 1.2 2005/04/22 21:57:08 tg Exp $

SHLIB_VERSION?= 7.0
LIB=		png
SRCS=		png.c pngerror.c pngget.c pngmem.c pngpread.c \
		pngread.c pngrio.c pngrtran.c pngrutil.c pngset.c \
		pngtrans.c pngwio.c pngwrite.c pngwtran.c pngwutil.c
DPADD+=		${LIBM} ${LIBZ}
LDADD+=		-lm -lz
MAN=		libpng.3 libpngpf.3 png.5
INCS=		png.h pngconf.h

.include <bsd.own.mk>
COPTS+=		-Wall
CPPFLAGS+=	-DPNG_NO_ASSEMBLER_CODE -DPNG_USE_PNGGCCRD

includes:
.for _i in ${INCS}
	cd ${.CURDIR}; cmp -s ${_i} ${DESTDIR}/usr/include/${_i} \
	    >/dev/null 2>&1 || ${INSTALL} ${INSTALL_COPY} \
	    -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${_i} ${DESTDIR}/usr/include/
.endfor

.include <bsd.lib.mk>
