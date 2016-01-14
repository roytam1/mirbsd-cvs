# $MirOS: src/usr.bin/ssh/ssh-keyscan/Makefile,v 1.2 2009/10/04 20:48:36 tg Exp $
# $OpenBSD: Makefile,v 1.5 2009/05/28 16:50:16 andreas Exp $

.PATH:		${.CURDIR}/..

PROG=	ssh-keyscan
BINOWN=	root

BINMODE?=555

BINDIR=	/usr/bin
MAN=	ssh-keyscan.1

SRCS=	ssh-keyscan.c

.include <bsd.prog.mk>

LDADD+= -lcrypto -lz
DPADD+= ${LIBCRYPTO} ${LIBZ}
