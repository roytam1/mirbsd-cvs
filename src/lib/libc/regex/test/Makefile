# $MirOS: src/lib/libc/regex/test/Makefile,v 1.1 2007/02/12 04:36:32 tg Exp $

all: ${PROG} regress

LIBCSRCDIR=	${.CURDIR}/../..
CPPFLAGS+=	-I${.CURDIR}/..
CDIAGFLAGS+=	-Wno-cast-qual
PROG=		re
SRCS=		debug.c main.c split.c
NOMAN=		Yes

regress: ${PROG} ${.CURDIR}/tests
	./${PROG} <${.CURDIR}/tests
	./${PROG} -el <${.CURDIR}/tests
	./${PROG} -er <${.CURDIR}/tests

.include <bsd.prog.mk>
