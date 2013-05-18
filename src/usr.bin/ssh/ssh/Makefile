# $MirOS$
# $OpenBSD: Makefile,v 1.51 2003/11/21 11:57:03 djm Exp $

.PATH:		${.CURDIR}/..

PROG=	ssh
BINOWN=	root

BINDIR=	/usr/bin
MAN=	ssh.1 ssh_config.5
LINKS=	${BINDIR}/ssh ${BINDIR}/slogin
MLINKS=	ssh.1 slogin.1

SRCS=	ssh.c readconf.c clientloop.c sshtty.c \
	sshconnect.c sshconnect1.c sshconnect2.c

.include <bsd.prog.mk>

DPADD+=	${LIBCRYPTO} ${LIBZ} ${LIBDES}
LDADD+=	-lcrypto -lz -ldes
