# $MirOS: src/sbin/savecore/Makefile,v 1.3 2007/05/08 21:52:55 tg Exp $
# $OpenBSD: Makefile,v 1.18 2005/06/26 18:21:25 otto Exp $

PROG=	savecore

SRCS=	savecore.c zopen.c
CPPFLAGS=-DSAVECORE -DZLIB_CONST
LDADD=	-lkvm -lz
DPADD=	${LIBKVM} ${LIBZ}
MAN=	savecore.8
.PATH:	${.CURDIR}/../../usr.bin/compress

.include <bsd.prog.mk>
