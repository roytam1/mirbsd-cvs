# $MirOS$

.include "../Makefile.inc"

SHLIB_VERSION?=	9.0
LIB=		iberty
SRCS=		_gplwarn.c argv.c concat.c copysign.c cp-demangle.c \
		cp-demint.c cplus-dem.c dyn-string.c fdmatch.c fibheap.c \
		floatformat.c getpwd.c getruntime.c hashtab.c hex.c \
		htab_old.c lbasename.c lrealpath.c make-relative-prefix.c \
		make-temp-file.c mempcpy.c objalloc.c obstack.c partition.c \
		pex-unix.c physmem.c safe-ctype.c sort.c spaces.c \
		splay-tree.c stpcpy.c stpncpy.c strerror.c strsignal.c \
		ternary.c xatexit.c xexit.c xmalloc.c xmemdup.c xstrdup.c \
		xstrerror.c
CPPFLAGS+=	-DHAVE_CONFIG_H -I${GNU_LIBIBERTY_SRC} -I${GNU_LIBIBERTY_INC}

.PATH: ${GNU_LIBIBERTY_SRC}
.PATH: ${GNU_LIBIBERTY_SRC}/testsuite
.PATH: ${GNUSYSTEM_AUX_DIR}

CFLAGS__gplwarn.o= -DMYNAME=\"libiberty\" -DGPLVER=\"2+\"

CLEANFILES+=	test-demangle test-demangle.o

check: test-demangle demangle-expected
	LD_LIBRARY_PATH=. ./test-demangle \
	    <${GNU_LIBIBERTY_SRC}/testsuite/demangle-expected

test-demangle: test-demangle.o ${_LIBS}
	${CC} -L. -o $@ test-demangle.o -liberty

test-demangle.o: test-demangle.c

.depend: test-demangle.c

.include <bsd.lib.mk>
