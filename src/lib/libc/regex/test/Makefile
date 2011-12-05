# $MirOS: src/lib/libc/regex/test/Makefile,v 1.2 2007/02/12 05:37:51 tg Exp $

all: ${PROG} regress

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
