# $MirOS: src/sys/arch/sparc/stand/libkern/Makefile,v 1.7 2007/03/02 03:13:27 tg Exp $
# $OpenBSD: Makefile,v 1.3 2003/06/01 17:00:39 deraadt Exp $

LIB=	kern

.PATH:	${.CURDIR}/../../../../lib/libkern
.PATH:	${.CURDIR}/../../../../lib/libkern/arch/sparc

.include "${.CURDIR}/../../../../lib/libkern/arch/sparc/Makefile.inc"

CPPFLAGS+= -I${.CURDIR}/../include -I${.CURDIR}/../../../.. \
	-I${.CURDIR}/../../../../lib/libkern \
	-I${.CURDIR}/../../../../lib/libkern/arch/sparc

AFLAGS=	-x assembler-with-cpp -traditional-cpp -I${.CURDIR}/../include \
	-I${.CURDIR}/../../../..  -I${.CURDIR}/../../../../lib/libkern \
	-I${.CURDIR}/../../../../lib/libkern/arch/sparc

# kern routines
SRCS=	__main.c bzero.S strcmp.c strncmp.c

SRCS+=	umul.S mul.S rem.S sdiv.S udiv.S urem.S
SRCS+=	saveregs.S

KERNBASE?=	${.CURDIR}/../../../../../kern
KERNSTAND=	#defined
SMALL=		#defined
.include "${KERNBASE}/c/Makefile.inc"
.include "${KERNBASE}/z/Makefile.adler32"

${OBJS}:	${.CURDIR}/../Makefile.inc

NOPIC=	yes

install:

.include <bsd.lib.mk>
