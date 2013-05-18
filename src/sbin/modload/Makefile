# $MirOS: src/sbin/modload/Makefile,v 1.3 2005/11/17 12:07:57 tg Exp $
# $OpenBSD: Makefile,v 1.4 2002/01/08 21:28:38 ericj Exp $

PROG=		modload
SRCS=		modload.c exec.c util.c
MAN=		modload.8

.include <bsd.own.mk>

.if ${OBJECT_FMT:U} == "ELF"
SRCS+=		elf.c exec_elf.c
CLEANFILES+=	a.out.o exec_aout.o
CPPFLAGS+=	-DELF_SUPPORT
.elif ${OBJECT_FMT:L} == "aout"
SRCS+=		a.out.c exec_aout.c
CLEANFILES+=	elf.o exec_elf.o
CPPFLAGS+=	-DUSE_AOUT -DAOUT_SUPPORT
.endif

CPPFLAGS+=	-DIN_MODLOAD
.PATH: ${BSDSRCDIR}/usr.sbin/config

.include <bsd.prog.mk>
