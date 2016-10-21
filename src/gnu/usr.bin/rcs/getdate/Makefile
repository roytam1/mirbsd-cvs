# $MirOS: src/gnu/usr.bin/rcs/getdate/Makefile,v 1.2 2005/12/05 22:33:23 tg Exp $

PROG=		getdate
SRCS=
OBJS=		getdate.o
NOMAN=		yes
CPPFLAGS+=	-DTEST

NEED_RCS_LIB=	No
.include "../Makefile.inc"

CPPFLAGS+=	-I${CVSLIB}

getdate.o: ${CVSLIB}/getdate.c

.include <bsd.prog.mk>
