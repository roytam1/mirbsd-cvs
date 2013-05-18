# $MirOS: src/sbin/growfs/Makefile,v 1.3 2005/03/15 19:03:53 tg Exp $
# @(#)Makefile	8.8 (Berkeley) 6/21/2000
# $TSHeader: src/sbin/growfs/Makefile,v 1.4 2000/12/05 19:45:24 tomsoft Exp $
# $FreeBSD: src/sbin/growfs/Makefile,v 1.5 2003/06/11 23:24:31 obrien Exp $

PROG=		growfs
SRCS=		growfs.c debug.c	# comment debug.c
CPPFLAGS+=	-DFS_DEBUG		# comment if not wanted
MAN=		growfs.8
CFLAGS+=	-Wall

DPADD=		${LIBUTIL}
LDADD=		-lutil

.include <bsd.prog.mk>
