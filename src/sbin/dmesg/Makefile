#	$OpenBSD: Makefile,v 1.5 2005/04/28 11:11:13 henning Exp $

PROG=	dmesg
MAN=	dmesg.8
LDADD=	-lkvm -lz
DPADD=	${LIBKVM} ${LIBZ}
CFLAGS+=-Wall

.include <bsd.prog.mk>
