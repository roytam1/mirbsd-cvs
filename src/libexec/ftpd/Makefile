# $MirOS: src/libexec/ftpd/Makefile,v 1.7 2007/04/18 19:45:58 tg Exp $
# $OpenBSD: Makefile,v 1.24 2005/06/15 16:13:27 mickey Exp $
# $NetBSD: Makefile,v 1.13 1996/02/16 02:07:41 cgd Exp $
# @(#)Makefile	8.2 (Berkeley) 4/4/94

PROG=		ftpd
SRCS=		ftpcmd.y ftpd.c logutmp.c logwtmp.c monitor.c \
		monitor_fdpass.c popen.c
MAN=		ftpd.8
YFLAGS=
CPPFLAGS+=	-DHASSETPROCTITLE -Dunix -DINET6
CFLAGS+=	-Wall

# our internal version of ls.
LSDIR=		${.CURDIR}/../../bin/ls
.PATH: ${LSDIR}

SRCS+=		ls.c cmp.c print.c util.c
.include <bsd.sys.mk>
CPPFLAGS+=	-idirafter ${LSDIR}

LDADD+=		-lutil
DPADD+=		${LIBUTIL}

.include <bsd.prog.mk>
