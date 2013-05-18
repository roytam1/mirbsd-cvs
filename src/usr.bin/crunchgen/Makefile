# $MirOS: src/usr.bin/crunchgen/Makefile,v 1.2 2007/02/18 02:39:14 tg Exp $
# $OpenBSD: Makefile,v 1.2 1996/09/25 06:40:52 etheisen Exp $

PROG=		crunchgen
SRCS=		crunchgen.c data.S
CFLAGS+=	-Wall
CPPFLAGS+=	-DMF_NAMES='"Makefile.bsd-wrapper","Makefile"'
AFLAGS+=	-Wa,-I${.CURDIR}

data.o: crunched_main.c

.include <bsd.prog.mk>
