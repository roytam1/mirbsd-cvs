# $MirOS: src/libexec/ftpd/Makefile,v 1.2 2005/03/06 19:24:00 tg Exp $
# $OpenBSD: Makefile,v 1.22 2004/01/05 02:55:28 espie Exp $
# $NetBSD: Makefile,v 1.13 1996/02/16 02:07:41 cgd Exp $
# @(#)Makefile	8.2 (Berkeley) 4/4/94

PROG=	ftpd
SRCS=	ftpd.c ftpcmd.y logutmp.c logwtmp.c popen.c
MAN=	ftpd.8
YFLAGS=
CPPFLAGS+=	-DHASSETPROCTITLE -Dunix -DINET6
CFLAGS+=	-Wall

.include <bsd.own.mk>

# our internal version of ls.
LSDIR=	${.CURDIR}/../../bin/ls
.PATH:	${LSDIR}
SRCS+=	ls.c cmp.c print.c util.c
CPPFLAGS+=	-idirafter ${LSDIR}

LDADD+=	-lutil
DPADD+=	${LIBUTIL}

.if ${TCP_WRAPPERS:L} == "yes"
CPPFLAGS+=	-DTCPWRAPPERS
LDADD+=		-lwrap
DPADD+=		${LIBWRAP}
.endif

.include <bsd.prog.mk>
