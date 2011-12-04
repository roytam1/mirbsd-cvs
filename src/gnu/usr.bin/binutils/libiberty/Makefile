# $MirOS: src/gnu/usr.bin/binutils/libiberty/Makefile,v 1.4 2005/06/05 21:36:39 tg Exp $

.include "../Makefile.inc"

LIB=		iberty
NOPIC=		Yes
SRCS=		_gplwarn.c argv.c concat.c copysign.c cp-demangle.c \
		cp-demint.c cplus-dem.c dyn-string.c fdmatch.c fibheap.c \
		floatformat.c fopen_unlocked.c getpwd.c getruntime.c \
		hashtab.c hex.c htab_old.c lbasename.c lrealpath.c \
		make-relative-prefix.c make-temp-file.c mempcpy.c objalloc.c \
		obstack.c partition.c pex-common.c pex-one.c pex-unix.c \
		pexecute.c physmem.c safe-ctype.c sort.c spaces.c \
		splay-tree.c stpcpy.c stpncpy.c strerror.c strndup.c \
		strsignal.c strverscmp.c ternary.c unlink-if-ordinary.c \
		xatexit.c xexit.c xmalloc.c xmemdup.c xstrdup.c xstrerror.c \
		xstrndup.c

CPPFLAGS+=	-DHAVE_CONFIG_H -I${GNU_LIBIBERTY_SRC} -I${GNU_LIBIBERTY_INC}

.PATH: ${GNU_LIBIBERTY_SRC}
.PATH: ${GNU_LIBIBERTY_SRC}/testsuite
.PATH: ${GNUSYSTEM_AUX_DIR}

CFLAGS__gplwarn.o= -DMYNAME=\"libiberty\" -DGPLVER=\"2+\"

CLEANFILES+=	test-demangle test-demangle.o test-pexecute test-pexecute.o

check: test-demangle demangle-expected test-pexecute
	./test-demangle <${GNU_LIBIBERTY_SRC}/testsuite/demangle-expected
	./test-pexecute

test-demangle: test-demangle.o ${_LIBS}
	${CC} -L. -o $@ test-demangle.o -liberty

test-demangle.o: test-demangle.c

test-pexecute: test-pexecute.o ${_LIBS}
	${CC} -L. -o $@ test-pexecute.o -liberty

test-pexecute.o: test-pexecute.c

.depend: test-demangle.c test-pexecute.c

.include <bsd.lib.mk>
