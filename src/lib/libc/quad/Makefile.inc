# $MirOS$
# $OpenBSD: Makefile.inc,v 1.4 2004/11/28 07:09:13 mickey Exp $

# Quad support
SRCS+=		fixdfdi.c fixsfdi.c fixunsdfdi.c fixunssfdi.c \
		floatdidf.c floatdisf.c floatunsdidf.c

.PATH: ${LIBCSRCDIR}/arch/${MACHINE_ARCH}/quad ${LIBCSRCDIR}/quad
