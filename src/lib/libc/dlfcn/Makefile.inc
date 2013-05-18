# $MirOS: src/lib/libc/dlfcn/Makefile.inc,v 1.2 2005/03/06 20:28:39 tg Exp $
# $OpenBSD: Makefile.inc,v 1.1 2001/11/20 01:09:38 pvalchev Exp $

.PATH: ${LIBCSRCDIR}/dlfcn

.include <bsd.own.mk>

.if ${OBJECT_FMT:U} == "ELF"
SRCS+=		dlfcn_stubs.c
CPPFLAGS+=	-I${.CURDIR}/dlfcn
CFLAGS_dlfcn_stubs.o+= -Wno-unused
.endif
