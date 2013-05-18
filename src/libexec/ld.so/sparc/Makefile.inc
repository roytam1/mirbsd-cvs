# $MirOS$
# $OpenBSD: Makefile.inc,v 1.2 2002/11/23 19:14:25 drahn Exp $

LIBCSRCDIR=	${.CURDIR}/../../lib/libc
COPTS+=		-fpic -msoft-float
CPPFLAGS+=	-I${LIBCSRCDIR}/arch/sparc -DSTRONG_SPARC
.include "${LIBCSRCDIR}/arch/sparc/Makefile.inc"
.PATH: ${LIBCSRCDIR}/arch/sparc/gen
SRCS+=		umul.S mul.S
