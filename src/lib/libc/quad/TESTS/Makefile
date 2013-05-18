# $MirOS$

.include <bsd.own.mk>

KERNBASE?=	${.CURDIR}/../../../../kern
NOMAN=		Yes
CLEANFILES+=	divrem divrem.o mul mul.o muldi3.o qdivrem.o
F=		MKC_DEBG=Yes

all:
	cd ${.CURDIR} && exec ${MAKE} $F mul PROG=mul \
	    SRCS='mul.c muldi3.c'
	cd ${.CURDIR} && exec ${MAKE} $F divrem PROG=divrem \
	    SRCS='divrem.c qdivrem.c'

.PATH: ${KERNBASE}/c

.include "${KERNBASE}/Makefile.inc"
.include <bsd.prog.mk>
