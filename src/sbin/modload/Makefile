# $MirOS$
# $OpenBSD: Makefile,v 1.4 2002/01/08 21:28:38 ericj Exp $

PROG=	modload
MAN=	modload.8

SRCS=	modload.c

.include <bsd.own.mk>

.if ${OBJECT_FMT:U} == "ELF"
SRCS+=	elf.c
.el${OBJECT_FMT:L} == "aout"
SRCS+=	a.out.c
CPPFLAGS+=	-DUSE_AOUT
.endif

.include <bsd.prog.mk>
