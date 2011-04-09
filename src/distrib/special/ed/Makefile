# $MirOS: src/distrib/special/ed/Makefile,v 1.1 2009/04/17 19:13:51 tg Exp $

.include <bsd.own.mk>

SRC_PATH=	${BSDSRCDIR}/bin/ed

PROG=		ed
SRCS=		buf.c glbl.c io.c main.c re.c sub.c undo.c
CPPFLAGS+=	-DBACKWARDS

.include <bsd.prog.mk>
