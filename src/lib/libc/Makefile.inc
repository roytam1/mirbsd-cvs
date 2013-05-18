# $MirOS: src/lib/libc/Makefile.inc,v 1.7 2006/11/21 01:04:08 tg Exp $
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
.include "${LIBCSRCDIR}/quad/Makefile.inc"
.include "${LIBCSRCDIR}/regex/Makefile.inc"
.include "${LIBCSRCDIR}/rpc/Makefile.inc"
.include "${LIBCSRCDIR}/stdio/Makefile.inc"
.include "${LIBCSRCDIR}/stdlib/Makefile.inc"
.include "${LIBCSRCDIR}/string/Makefile.inc"
.include "${LIBCSRCDIR}/sys/Makefile.inc"
.include "${LIBCSRCDIR}/termios/Makefile.inc"
.include "${LIBCSRCDIR}/thread/Makefile.inc"
.include "${LIBCSRCDIR}/time/Makefile.inc"

.for _z _q _s in ${UNIFDEF_SRCS}
SRCS+=		${_z}
CLEANFILES+=	${_z}

${_z}: ${_q}
	-unifdef -D${_s} $> >$@

beforedepend: ${_z}
.endfor

LIBKERN=	${LIBCSRCDIR}/../../sys/lib/libkern

KSRCS=	memcmp.c bzero.c ffs.c strcmp.c strlen.c strncmp.c \
	strncpy.c htonl.c htons.c ntohl.c ntohs.c
KSRCS+=	adddi3.c anddi3.c ashldi3.c ashrdi3.c cmpdi2.c divdi3.c iordi3.c \
	lshldi3.c lshrdi3.c moddi3.c muldi3.c negdi2.c notdi2.c qdivrem.c \
	subdi3.c  ucmpdi2.c udivdi3.c umoddi3.c xordi3.c
KINCLUDES+=	quad/quad.h
