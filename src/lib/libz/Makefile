# $MirOS: src/lib/libz/Makefile,v 1.25 2008/08/01 15:47:55 tg Exp $

LIB=		z
SHLIB_VERSION?=	5.4

KERNBASE?=	${BSDSRCDIR}/kern
KERNNOGCC=	#defined

.include <bsd.own.mk>
.include "${KERNBASE}/z/Makefile.adler32"
.include "${KERNBASE}/z/Makefile.inc"

SRCS+=		${ZLIB_SRCS}
HDRS=		zconf.h zlib.h
HDRSRC=		${KERNBASE}/include
CLEANFILES+=	${ZLIB_CLEANFLS}
CPPFLAGS+=	-DZLIB_CONST
COPTS+=		-Wall -Wno-old-style-definitions
MAN=		compress.3

beforedepend: ${ZLIB_GENHDRS}

MLINKS=	compress.3 zlibVersion.3 compress.3 deflateInit.3 \
	compress.3 deflate.3 compress.3 deflateEnd.3 \
	compress.3 inflateInit.3 compress.3 inflate.3 \
	compress.3 inflateEnd.3 compress.3 deflateInit2.3 \
	compress.3 deflateSetDictionary.3 \
	compress.3 deflateCopy.3 compress.3 deflateReset.3 \
	compress.3 deflateParams.3 compress.3 deflateTune.3 \
	compress.3 deflateBound.3 \
	compress.3 deflatePrime.3 compress.3 deflateSetHeader.3 \
	compress.3 inflateInit2.3 \
	compress.3 inflateSetDictionary.3 compress.3 inflateSync.3 \
	compress.3 inflateCopy.3 compress.3 inflateReset.3 \
	compress.3 inflatePrime.3 compress.3 inflateGetHeader.3 \
	compress.3 inflateBackInit.3 compress.3 inflateBack.3 \
	compress.3 inflateBackEnd.3 compress.3 zlibCompileFlags.3 \
	compress.3 compress2.3 compress.3 compressBound.3 \
	compress.3 uncompress.3 compress.3 gzopen.3 \
	compress.3 gzdopen.3 compress.3 gzsetparams.3 \
	compress.3 gzread.3 compress.3 gzwrite.3 \
	compress.3 gzprintf.3 compress.3 gzputs.3 \
	compress.3 gzgets.3 compress.3 gzputc.3 \
	compress.3 gzgetc.3 compress.3 gzungetc.3 \
	compress.3 gzflush.3 \
	compress.3 gzseek.3 compress.3 gzrewind.3 \
	compress.3 gztell.3 compress.3 gzeof.3 \
	compress.3 gzdirect.3 \
	compress.3 gzclose.3 compress.3 gzerror.3 \
	compress.3 gzclearerr.3 \
	compress.3 adler32_combine.3 \
	compress.3 crc32.3 compress.3 crc32_combine.3

# MirOS extension
SRCS+=		gzfopen.c
MAN+=		gzfopen.3
MLINKS+=	gzfopen.3 gzfdopen.3

afterinstall:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${.CURDIR}/zlib.pc ${DESTDIR}/usr/libdata/pkgconfig/

.include <bsd.lib.mk>
