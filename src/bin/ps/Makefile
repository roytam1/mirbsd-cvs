# $MirOS: src/bin/ps/Makefile,v 1.3 2006/01/31 22:41:09 tg Exp $
# $OpenBSD: Makefile,v 1.8 2002/06/08 22:41:46 art Exp $

PROG=	ps
SRCS=	fmt.c keyword.c nlist.c print.c ps.c
DPADD+=	${LIBM} ${LIBKVM} ${LIBZ}
LDADD+=	-lm -lkvm -lz

CFLAGS_print.o+= -Wno-format-y2k

.include <bsd.prog.mk>

