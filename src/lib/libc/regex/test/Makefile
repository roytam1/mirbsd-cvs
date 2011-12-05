# $MirOS: src/lib/libc/regex/test/Makefile,v 1.3 2007/02/12 05:45:54 tg Exp $

all: ${PROG} regress

tlc:
	cd ${.CURDIR} && exec ${MAKE} _MODSRC_LIB_LIBC_REGEX_NOSRCS=1 all

LIBCSRCDIR=	${.CURDIR}/../..
CPPFLAGS+=	-I${.CURDIR}/..
PROG=		re
SRCS=		debug.c main.c split.c
NOMAN=		Yes

regress: ${PROG} ${.CURDIR}/tests
	./${PROG} <${.CURDIR}/tests
	./${PROG} -el <${.CURDIR}/tests
	./${PROG} -er <${.CURDIR}/tests

.include <bsd.prog.mk>
