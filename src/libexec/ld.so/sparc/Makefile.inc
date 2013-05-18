# $MirOS: src/libexec/ld.so/sparc/Makefile.inc,v 1.2 2006/06/30 18:11:02 tg Exp $
# $OpenBSD: Makefile.inc,v 1.2 2002/11/23 19:14:25 drahn Exp $

LIBCSRCDIR=	${.CURDIR}/../../lib/libc
COPTS+=		-fpic -msoft-float
CPPFLAGS+=	-I${LIBCSRCDIR}/arch/sparc -DSTRONG_SPARC
.include "${LIBCSRCDIR}/arch/sparc/Makefile.inc"
.PATH: ${LIBCSRCDIR}/arch/sparc/gen
SRCS+=		umul.S mul.S

.PATH: ${LIBCSRCDIR}/string
SRCS+=		bcopy.c
CFLAGS_bcopy.o=	-UMEMMOVE -DMEMCOPY
