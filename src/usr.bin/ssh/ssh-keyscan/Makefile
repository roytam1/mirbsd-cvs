# $MirOS$
# $OpenBSD: Makefile,v 1.5 2009/05/28 16:50:16 andreas Exp $

.PATH:		${.CURDIR}/..

PROG=	ssh-keyscan
BINOWN=	root

BINMODE?=555

BINDIR=	/usr/bin
MAN=	ssh-keyscan.1

SRCS=	ssh-keyscan.c

.include <bsd.prog.mk>

LDADD+= -lcrypto -lz ${LD_R_OFF}
DPADD+= ${LIBCRYPTO} ${LIBZ} ${DP_R_OFF}
