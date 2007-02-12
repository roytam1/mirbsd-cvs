# $MirOS$

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
