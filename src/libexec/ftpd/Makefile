# $MirOS: src/libexec/ftpd/Makefile,v 1.4 2005/03/29 02:19:33 tg Exp $
# $OpenBSD: Makefile,v 1.23 2004/11/28 18:49:29 henning Exp $
# $NetBSD: Makefile,v 1.13 1996/02/16 02:07:41 cgd Exp $
# @(#)Makefile	8.2 (Berkeley) 4/4/94

PROG=	ftpd
SRCS=	ftpd.c ftpcmd.y logutmp.c logwtmp.c monitor.c monitor_fdpass.c popen.c
MAN=	ftpd.8
YFLAGS=
CPPFLAGS+=	-DHASSETPROCTITLE -Dunix -DINET6
CFLAGS+=	-Wall

# our internal version of ls.
LSDIR=		${.CURDIR}/../../bin/ls
.PATH:	${LSDIR}

SRCS+=		ls.c cmp.c print.c util.c
CPPFLAGS+=	-idirafter ${LSDIR}

LDADD+=	-lutil
DPADD+=	${LIBUTIL}

.include <bsd.prog.mk>
