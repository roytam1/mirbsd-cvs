# $MirOS: src/usr.bin/ssh/ssh/Makefile,v 1.2 2005/03/13 18:33:35 tg Exp $
# $OpenBSD: Makefile,v 1.52 2008/05/09 14:18:45 djm Exp $

.PATH:		${.CURDIR}/..

PROG=	ssh
BINOWN=	root

BINDIR=	/usr/bin
MAN=	ssh.1 ssh_config.5
LINKS=	${BINDIR}/ssh ${BINDIR}/slogin
MLINKS=	ssh.1 slogin.1

SRCS=	ssh.c readconf.c clientloop.c sshtty.c \
	sshconnect.c sshconnect1.c sshconnect2.c mux.c

.include <bsd.prog.mk>

DPADD+=	${LIBCRYPTO} ${LIBZ} ${LIBDES}
LDADD+=	-lcrypto -lz -ldes
