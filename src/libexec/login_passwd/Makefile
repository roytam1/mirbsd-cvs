# $MirOS$
# $OpenBSD: Makefile,v 1.4 2004/05/12 20:43:44 millert Exp $

PROG=	login_passwd
MAN=	login_passwd.8
SRCS=	login.c login_passwd.c
DPADD=	${LIBUTIL}
LDADD=	-lutil
CFLAGS+=-Wall
CPPFLAGS+=-DPASSWD

BINOWN=	root
BINGRP=	_shadow
BINMODE=2555		# no SUID root, because no YP here
BINDIR=	/usr/libexec/auth

.include <bsd.prog.mk>
