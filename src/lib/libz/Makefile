# $MirOS: src/lib/libz/Makefile,v 1.8 2005/07/09 13:20:44 tg Exp $
# $OpenBSD: Makefile,v 1.13 2005/07/20 21:29:00 jmc Exp $

SHLIB_VERSION?=	5.2
LIB=		z
HDRS=		zconf.h zlib.h
SRCS=		adler32.c compress.c crc32.c deflate.c gzio.c infback.c \
		inffast.c inflate.c inftrees.c trees.c uncompr.c zutil.c
MAN=		compress.3
CFLAGS+=	-Wall
CDIAGFLAGS+=	-Wno-old-style-definitions -Wno-cast-qual
CPPFLAGS+=	-I. -DHAVE_STRERROR -DHAS_vsnprintf -DHAS_snprintf
GENHDRS=	crc32.h inffixed.h trees.h
CLEANFILES+=	mk_crc32 mk_crc32.c mk_inffixed mk_inffixed.c \
		mk_trees mk_trees.c ${GENHDRS}

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
	compress.3 adler32.3 compress.3 adler32_combine.3 \
	compress.3 crc32.3 compress.3 crc32_combine.3

includes:
.for _i in ${HDRS}
	cd ${.CURDIR} && cmp -s ${_i} ${DESTDIR}/usr/include/${_i} || \
	    ${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} \
	    -m ${NONBINMODE} ${_i} ${DESTDIR}/usr/include/
.endfor

HOSTCFLAGS?=	${CFLAGS}
HOSTLDFLAGS?=	${LDFLAGS}
HOSTCFLAGS+=	${CPPFLAGS} -I${.CURDIR}

beforedepend: ${GENHDRS}

crc32.h: mk_crc32
	./mk_crc32

inffixed.h: mk_inffixed
	./mk_inffixed >$@

trees.h: mk_trees
	./mk_trees

mk_crc32.c:
	print 'void get_crc_table(void);' >$@
	print 'int' >>$@
	print 'main(void)' >>$@
	print '{' >>$@
	print '\tget_crc_table();' >>$@
	print '\treturn 0;' >>$@
	print '}' >>$@

mk_crc32: mk_crc32.c crc32.c
	${HOSTCC} ${LDSTATIC} ${HOSTCFLAGS} ${HOSTLDFLAGS} -DMAKECRCH \
	    $> -o $@

mk_inffixed.c: crc32.h
	print 'void makefixed(void);' >$@
	print 'int' >>$@
	print 'main(void)' >>$@
	print '{' >>$@
	print '\tmakefixed();' >>$@
	print '\treturn 0;' >>$@
	print '}' >>$@

mk_inffixed: mk_inffixed.c inflate.c \
    adler32.c crc32.c inffast.c inftrees.c zutil.c
	${HOSTCC} ${LDSTATIC} ${HOSTCFLAGS} ${HOSTLDFLAGS} -DMAKEFIXED \
	    $> -o $@

mk_trees.c:
	print 'void _tr_init(void);' >$@
	print 'int' >>$@
	print 'main(void)' >>$@
	print '{' >>$@
	print '\t_tr_init();' >>$@
	print '\treturn 0;' >>$@
	print '}' >>$@

mk_trees: mk_trees.c trees.c
	${HOSTCC} ${LDSTATIC} ${HOSTCFLAGS} ${HOSTLDFLAGS} -DGEN_TREES_H \
	    $> -o $@

.include <bsd.lib.mk>
