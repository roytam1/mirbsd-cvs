# $MirOS: src/libexec/ld.so/Makefile,v 1.2 2005/03/06 19:24:01 tg Exp $
# $OpenBSD: Makefile,v 1.25 2005/03/23 19:48:05 drahn Exp $

.include "Makefile.inc"

SUBDIR=	ldconfig ldd
VPATH=	${.CURDIR}/../../lib/libc/string

PROG=	ld.so
MAN=	ld.so.1
SRCS=	ldasm.S loader.c resolve.c dlfcn.c dl_printf.c rtld_machine.c
SRCS+=	util.c sod.c strsep.c strtol.c dir.c library_subr.c
.if ${MACHINE_ARCH} == "i386"
SRCS+=	library_mquery.c
.else
SRCS+=	library.c
.endif

.include "${.CURDIR}/${MACHINE_ARCH}/Makefile.inc"
.PATH:	${.CURDIR}/${MACHINE_ARCH}

CPPFLAGS+=	-I${.CURDIR}/${MACHINE_ARCH} -Dstrsep=_dl_strsep
CFLAGS_loader.o=-fno-stack-protector-all	# gcc mis-compiles
INSTALL_STRIP=

ELF_LDFLAGS+=	--shared -Bsymbolic

${PROG}:
	${LD} -x -e _dl_start ${ELF_LDFLAGS} -o ${PROG} ${OBJS} ${LDADD}

.include <bsd.prog.mk>
