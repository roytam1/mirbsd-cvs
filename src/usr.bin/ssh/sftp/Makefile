# $MirOS: src/usr.bin/ssh/sftp/Makefile,v 1.4 2008/12/16 20:55:34 tg Exp $
# $OpenBSD: Makefile,v 1.11 2008/04/18 12:32:11 djm Exp $

.PATH:		${.CURDIR}/..

PROG=	sftp
BINOWN=	root

BINMODE?=555

BINDIR=	/usr/bin
MAN=	sftp.1

SRCS=	sftp.c sftp-client.c sftp-common.c sftp-glob.c

CFLAGS_sftp.o+=		-Wno-unused

.include <bsd.prog.mk>

LDADD+=	-ledit -ltermcap -lutil
DPADD+=	${LIBEDIT} ${LIBTERMCAP} ${LIBUTIL}
