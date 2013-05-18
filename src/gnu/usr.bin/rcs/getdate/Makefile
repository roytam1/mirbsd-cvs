# $MirOS: src/gnu/usr.bin/rcs/getdate/Makefile,v 1.1 2005/04/19 21:30:32 tg Exp $

PROG=		getdate
SRCS=
OBJS=		getdate.o
NOMAN=		yes
CPPFLAGS+=	-DTEST

.include "../Makefile.inc"

CPPFLAGS+=	-I${CVSLIB}

getdate.o: ${CVSLIB}/getdate.c

.include <bsd.prog.mk>
