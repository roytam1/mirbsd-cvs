# $MirOS: src/sbin/modload/Makefile,v 1.2 2005/03/06 19:50:16 tg Exp $
# $OpenBSD: Makefile,v 1.4 2002/01/08 21:28:38 ericj Exp $

PROG=		modload
SRCS=		modload.c
MAN=		modload.8

.include <bsd.own.mk>

.if ${OBJECT_FMT:U} == "ELF"
SRCS+=		elf.c
CLEANFILES+=	a.out.o
.elif ${OBJECT_FMT:L} == "aout"
SRCS+=		a.out.c
CLEANFILES+=	elf.o
CPPFLAGS+=	-DUSE_AOUT
.endif

.include <bsd.prog.mk>
