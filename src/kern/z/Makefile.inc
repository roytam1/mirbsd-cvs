# $MirOS: src/lib/libz/Makefile.gen,v 1.5 2007/04/17 22:10:58 tg Exp $

zlib_depends: crc32.h inffixed.h trees.h

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
    adler32.c crc32.c inffast.c inftrees.c zutil.c
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
