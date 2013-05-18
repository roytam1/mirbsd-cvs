# $MirOS: src/lib/libc/Makefile.inc,v 1.12 2009/09/15 16:27:29 tg Exp $
# $OpenBSD: Makefile.inc,v 1.11 2005/06/17 20:37:31 drahn Exp $

.ifndef LIBCSRCDIR
all:
	@echo "need to define LIBCSRCDIR" >&2; exit 1
.endif

CPPFLAGS+=	-DLIBC_SCCS -DSYSLIBC_SCCS
CPPFLAGS+=	-I${LIBCSRCDIR}/include

LLIBS=
AINC=   -I${LIBCSRCDIR}/arch/${MACHINE_ARCH}
.if defined(DESTDIR)
AINC+=  -nostdinc -idirafter ${DESTDIR}/usr/include
.endif

.if exists (${LIBCSRCDIR}/arch/${MACHINE_ARCH}/Makefile.inc)
.PATH:	${LIBCSRCDIR}/arch/${MACHINE_ARCH}
.include "${LIBCSRCDIR}/arch/${MACHINE_ARCH}/Makefile.inc"
.endif

.include "${LIBCSRCDIR}/compat-43/Makefile.inc"
.include "${LIBCSRCDIR}/crypt/Makefile.inc"
.include "${LIBCSRCDIR}/db/Makefile.inc"
.include "${LIBCSRCDIR}/dlfcn/Makefile.inc"
.include "${LIBCSRCDIR}/gen/Makefile.inc"
.include "${LIBCSRCDIR}/hash/Makefile.inc"
.include "${LIBCSRCDIR}/i18n/Makefile.inc"
.include "${LIBCSRCDIR}/net/Makefile.inc"
.include "${LIBCSRCDIR}/ohash/Makefile.inc"
.include "${LIBCSRCDIR}/regex/Makefile.inc"
.include "${LIBCSRCDIR}/rpc/Makefile.inc"
.include "${LIBCSRCDIR}/stdio/Makefile.inc"
.include "${LIBCSRCDIR}/stdlib/Makefile.inc"
.include "${LIBCSRCDIR}/string/Makefile.inc"
.include "${LIBCSRCDIR}/sys/Makefile.inc"
.include "${LIBCSRCDIR}/termios/Makefile.inc"
.include "${LIBCSRCDIR}/thread/Makefile.inc"
.include "${LIBCSRCDIR}/thread-stub/Makefile.inc"
.include "${LIBCSRCDIR}/time/Makefile.inc"

LIBKERN=	${LIBCSRCDIR}/../../sys/lib/libkern
