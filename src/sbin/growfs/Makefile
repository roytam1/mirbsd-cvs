# $MirOS: src/sbin/growfs/Makefile,v 1.2 2005/03/06 19:49:58 tg Exp $
# @(#)Makefile	8.8 (Berkeley) 6/21/2000
# $TSHeader: src/sbin/growfs/Makefile,v 1.4 2000/12/05 19:45:24 tomsoft Exp $
# $FreeBSD: src/sbin/growfs/Makefile,v 1.5 2003/06/11 23:24:31 obrien Exp $

# Define this to include debugging code
GFSDBG=		YES

PROG=		growfs
MAN=		growfs.8
CFLAGS+=	-Wall

DPADD=		${LIBUTIL}
LDADD=		-lutil

.if defined(GFSDBG)
SRCS+=		debug.c
CPPFLAGS+=	-DFS_DEBUG
.endif

.include <bsd.prog.mk>
