# $MirOS: src/usr.bin/ssh/sftp/Makefile,v 1.3 2006/04/19 10:40:59 tg Exp $
# $OpenBSD: Makefile,v 1.11 2008/04/18 12:32:11 djm Exp $

.PATH:		${.CURDIR}/..

PROG=	sftp
BINOWN=	root

BINMODE?=555

BINDIR=	/usr/bin
MAN=	sftp.1

SRCS=	sftp.c sftp-client.c sftp-common.c sftp-glob.c

.include <bsd.prog.mk>

LDADD+=	-ledit -ltermcap -lutil
DPADD+=	${LIBEDIT} ${LIBTERMCAP} ${LIBUTIL}
