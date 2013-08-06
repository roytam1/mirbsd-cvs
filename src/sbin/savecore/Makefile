# $MirOS: src/sbin/savecore/Makefile,v 1.4 2013/08/05 22:06:14 tg Exp $
# $OpenBSD: Makefile,v 1.18 2005/06/26 18:21:25 otto Exp $

PROG=	savecore

SRCS=	savecore.c zopen.c
CPPFLAGS=-DSAVECORE
LDADD=	-lkvm -lz
DPADD=	${LIBKVM} ${LIBZ}
MAN=	savecore.8
.PATH:	${.CURDIR}/../../usr.bin/compress

.include <bsd.prog.mk>
