# $MirOS: src/usr.sbin/traceroute6/Makefile,v 1.2 2008/03/27 13:41:34 tg Exp $
# $OpenBSD: Makefile,v 1.5 2004/11/10 22:07:46 drahn Exp $

PROG=	traceroute6
BINOWN=	root
BINGRP=	bin
BINMODE=4555
BINDIR?=/usr/dsbin

CPPFLAGS+=-DINET6 -DHAVE_POLL

MAN=	traceroute6.8

.include <bsd.prog.mk>
