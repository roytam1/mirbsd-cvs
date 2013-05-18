# $MirOS: src/usr.bin/fstat/Makefile,v 1.2 2005/03/15 19:23:50 tg Exp $
# $OpenBSD: Makefile,v 1.8 2001/06/27 06:16:49 art Exp $

PROG=	fstat
DPADD=	${LIBKVM} ${LIBZ}
SRCS=	fstat.c isofs.c
LDADD=	-lkvm -lz
BINGRP=	kmem
BINMODE=2555

CPPFLAGS+=-DINET6

.include <bsd.prog.mk>

