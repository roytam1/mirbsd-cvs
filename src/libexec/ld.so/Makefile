# $MirOS: src/libexec/ld.so/Makefile,v 1.11 2008/10/16 14:32:16 tg Exp $
# $OpenBSD: Makefile,v 1.34 2006/05/11 22:03:22 deraadt Exp $

SUBDIR=		ldconfig ldd
#SUBDIR+=	prebind
LIBCSRCDIR?=	${.CURDIR}/../../lib/libc
VPATH=		${LIBCSRCDIR}/string

SRCS=	ldasm.S loader.c resolve.c dlfcn.c dl_printf.c rtld_machine.c
SRCS+=	util.c sod.c strsep.c strtol.c dir.c library_subr.c dl_prebind.c
.if (${MACHINE_ARCH} == "i386")
SRCS+=	library_mquery.c
.else
SRCS+=	library.c
.endif

SRCS+=		ssp.c
CFLAGS_ssp.o=	-fno-stack-protector

PROG=		ld.so
DPADD+=		${LIBMDSUP}
LDADD+=		-lmdsup_pic

.include "Makefile.inc"
.include "${.CURDIR}/${MACHINE_ARCH}/Makefile.inc"
.PATH:	${.CURDIR}/${MACHINE_ARCH}

COPTS+=		-Wall
CPPFLAGS+=	-I${.CURDIR}/${MACHINE_ARCH} -Dstrsep=_dl_strsep
INSTALL_STRIP=

ELF_LDFLAGS+=	--shared -Bsymbolic --no-undefined

CLEANFILES+=	${PROG}~
${PROG}:
	${LD} -r -o ${PROG}~ ${OBJS}
	objcopy --redefine-sym memcpy=_dl_memcpy ${PROG}~
	${LD} -x -e _dl_start ${ELF_LDFLAGS} -o ${PROG} ${PROG}~ ${LDADD}

.include <bsd.prog.mk>
