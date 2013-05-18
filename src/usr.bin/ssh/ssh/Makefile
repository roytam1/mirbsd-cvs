# $MirOS: src/usr.bin/ssh/ssh/Makefile,v 1.3 2008/12/16 20:55:35 tg Exp $
# $OpenBSD: Makefile,v 1.53 2009/05/28 16:50:16 andreas Exp $

.PATH:		${.CURDIR}/..

PROG=	ssh
BINOWN=	root

BINDIR=	/usr/bin
MAN=	ssh.1 ssh_config.5
LINKS=	${BINDIR}/ssh ${BINDIR}/slogin
MLINKS=	ssh.1 slogin.1

SRCS=	ssh.c readconf.c clientloop.c sshtty.c \
	sshconnect.c sshconnect1.c sshconnect2.c mux.c \
	roaming_common.c

CFLAGS_clientloop.o+=	-Wno-unused
CFLAGS_sshconnect2.o+=	-Wno-unused

.include <bsd.prog.mk>

DPADD+=	${LIBCRYPTO} ${LIBZ} ${LIBDES}
LDADD+=	-lcrypto -lz -ldes
