# $MirOS$
# $OpenBSD: Makefile,v 1.17 2003/10/31 04:05:29 drahn Exp $

PROG=	kbd
SRCS=	main.c kbd_wscons.c
MAN=	kbd.8
LDADD=	-lkvm
DPADD=	${LIBKVM}

.include <bsd.prog.mk>
