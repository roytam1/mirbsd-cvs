# $MirOS: src/kern/z/Makefile.inc,v 1.5 2009/01/03 16:12:23 tg Exp $

.include "${KERNBASE}/Makefile.inc"

.PATH: ${KERNBASE}/z

ZLIB_GENHDRS=	crc32.h inffixed.h trees.h
ZLIB_CLEANFLS=	${ZLIB_GENHDRS} {mk_crc32,mk_inffixed,mk_trees}*
ZLIB_SRCS=	adler32cb.c compress.c crc32.c deflate.c gzclose.c gzlib.c \
		gzread.c gzwrite.c infback.c inffast.c inflate.c inftrees.c \
		trees.c uncompr.c zutil.c
ZLIB_SRCS+=	crc32_combine.c
ZLIB_CLEANFLS+=	crc32_combine.c
ZLIB_OBJS=	${ZLIB_SRCS:S/.c$/.o/}
HOSTCC?=	${CC}
HOSTCFLAGS?=	${CFLAGS}
HOSTLDFLAGS?=	${LDFLAGS}
HOSTCPPFLAGS?=	${CPPFLAGS}
.if ${CPPFLAGS:N1:S-I${KERNBASE}/z1:M1} == ""
CPPFLAGS+=	-I${KERNBASE}/z
.endif
.if ${CPPFLAGS:M-I.} == ""
CPPFLAGS+=	-I.
.endif
.if ${HOSTCPPFLAGS:N1:S-I${KERNBASE}/z1:M1} == ""
HOSTCPPFLAGS+=	-I${KERNBASE}/z
.endif
.if ${HOSTCPPFLAGS:M-I.} == ""
HOSTCPPFLAGS+=	-I.
.endif

crc32.h: mk_crc32
	./mk_crc32

inffixed.h: mk_inffixed
	./mk_inffixed >$@

trees.h: mk_trees
	./mk_trees

mk_crc32.c:
	print 'void get_crc_table(void);' >$@
	print >>$@
	print 'int' >>$@
	print 'main(void)' >>$@
	print '{' >>$@
	print '\tget_crc_table();' >>$@
	print '\treturn (0);' >>$@
	print '}' >>$@

mk_crc32: mk_crc32.c crc32.c
	${HOSTCC} ${LDSTATIC} ${HOSTCFLAGS} ${HOSTCPPFLAGS} \
	    ${HOSTLDFLAGS} -DMAKECRCH -DZLIB_NO_CRC32PUSH $> -o $@

mk_inffixed.c: crc32.h
	print 'void makefixed(void);' >$@
	print >>$@
	print 'int' >>$@
	print 'main(void)' >>$@
	print '{' >>$@
	print '\tmakefixed();' >>$@
	print '\treturn (0);' >>$@
	print '}' >>$@

mk_inffixed: mk_inffixed.c inflate.c \
    adler32s.c crc32.c inffast.c inftrees.c zutil.c
	${HOSTCC} ${LDSTATIC} ${HOSTCFLAGS} ${HOSTCPPFLAGS} \
	    ${HOSTLDFLAGS} -DMAKEFIXED -DZLIB_NO_ADLERPUSH $> -o $@

mk_trees.c:
	print '#include "deflate.h"' >$@
	print '#include <string.h>' >>$@
	print >>$@
	print 'int' >>$@
	print 'main(void)' >>$@
	print '{' >>$@
	print '\tdeflate_state s;' >>$@
	print >>$@
	print '\tbzero(&s, sizeof (s));' >>$@
	print '\t_tr_init(&s);' >>$@
	print '\treturn (0);' >>$@
	print '}' >>$@

mk_trees: mk_trees.c trees.c
	${HOSTCC} ${LDSTATIC} ${HOSTCFLAGS} ${HOSTCPPFLAGS} \
	    ${HOSTLDFLAGS} -DGEN_TREES_H $> -o $@

crc32_combine.c: crc32.c
	-unifdef -DL_crc32_combine $> >$@
