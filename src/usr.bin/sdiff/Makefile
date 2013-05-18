# $MirOS$
# $OpenBSD: Makefile,v 1.4 2006/02/20 08:38:18 otto Exp $

PROG=		sdiff
SRCS+=		common.c edit.c sdiff.c

.include <bsd.own.mk>
COPTS+=		-Wall -Wextra

DPADD+=		${LIBUTIL}
LDADD+=		-lutil

.include <bsd.prog.mk>
