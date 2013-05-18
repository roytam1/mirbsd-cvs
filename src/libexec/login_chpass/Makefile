# $MirOS: src/libexec/login_chpass/Makefile,v 1.2 2005/03/06 19:24:04 tg Exp $
# $OpenBSD: Makefile,v 1.4 2003/07/15 19:02:19 deraadt Exp $

PROG=	login_chpass
MAN=	login_chpass.8

.PATH:  ${.CURDIR}/../../usr.bin/passwd

CFLAGS+=-Wall

BINOWN=	root
BINGRP=	auth
BINMODE=4555
BINDIR=	/usr/libexec/auth

.include <bsd.prog.mk>
