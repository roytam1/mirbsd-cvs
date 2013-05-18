# $MirOS: src/usr.bin/ssh/sftp/Makefile,v 1.2 2005/03/13 18:33:35 tg Exp $
# $OpenBSD: Makefile,v 1.10 2006/04/18 10:44:28 dtucker Exp $

.PATH:		${.CURDIR}/..

PROG=	sftp
BINOWN=	root

BINMODE?=555

BINDIR=	/usr/bin
MAN=	sftp.1

SRCS=	sftp.c sftp-client.c sftp-common.c sftp-glob.c

.include <bsd.prog.mk>

LDADD+=	-ledit -ltermcap
DPADD+=	${LIBEDIT} ${LIBTERMCAP}
