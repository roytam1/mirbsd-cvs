# $MirOS$
# $OpenBSD: Makefile,v 1.9 2003/12/03 22:28:01 grange Exp $

.include <bsd.own.mk>

.if (!exists(arch/${MACHINE}/Makefile.inc) && \
    !exists(arch/${MACHINE_ARCH}/Makefile.inc))
NOMAN=	yes
NOPROG=	yes
.else

PROG=	pmdb
SRCS=	pmdb.c symbol.c clit.c process.c signal.c break.c core.c

.if ${OBJECT_FMT:U} == "ELF"
SRCS+=		elf_syms.c
CPPFLAGS+=	-DPMDB_ELF
.else
SRCS+=		aout_syms.c
CPPFLAGS+=	-DPMDB_AOUT
.endif

LDADD=		-ledit -lcurses
DPADD=		${LIBEDIT} ${LIBCURSES}

.if exists(arch/${MACHINE}/Makefile.inc)
.PATH: ${.CURDIR}/arch/${MACHINE}
.include "arch/${MACHINE}/Makefile.inc"
CPPFLAGS+=	-I${.CURDIR}/arch/${MACHINE}
.endif

.if (${MACHINE_ARCH} != ${MACHINE}) && exists(arch/${MACHINE_ARCH}/Makefile.inc)
.PATH: ${.CURDIR}/arch/${MACHINE_ARCH}
.include "arch/${MACHINE_ARCH}/Makefile.inc"
CPPFLAGS+=	-I${.CURDIR}/arch/${MACHINE_ARCH}
.endif

CFLAGS+=	-Wall -Wno-uninitialized

.endif

.include <bsd.prog.mk>
