# $MirOS: src/libexec/ftpd/Makefile,v 1.3 2005/03/15 18:27:25 tg Exp $
# $OpenBSD: Makefile,v 1.22 2004/01/05 02:55:28 espie Exp $
# $NetBSD: Makefile,v 1.13 1996/02/16 02:07:41 cgd Exp $
# @(#)Makefile	8.2 (Berkeley) 4/4/94

PROG=	ftpd
SRCS=	ftpd.c ftpcmd.y logutmp.c logwtmp.c popen.c
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
