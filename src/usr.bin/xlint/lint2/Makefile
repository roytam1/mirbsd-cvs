# $MirOS$
# $OpenBSD: Makefile,v 1.2 1996/06/26 05:44:21 deraadt Exp $
# $NetBSD: Makefile,v 1.2 1995/07/03 21:24:39 cgd Exp $

.PATH:	${.CURDIR}/../lint1

PROG=		lint2
SRCS=		chk.c emit.c emit2.c hash.c main2.c mem.c mem2.c msg.c read.c
NOMAN=		yes
CPPFLAGS+=	-I${.CURDIR}/../lint1
LINTFLAGS=	-abehrz
BINDIR=		/usr/libexec

.include <bsd.prog.mk>
