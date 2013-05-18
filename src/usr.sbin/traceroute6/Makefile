# $MirOS: src/usr.sbin/traceroute6/Makefile,v 1.3 2008/03/27 14:53:25 tg Exp $
# $OpenBSD: Makefile,v 1.5 2004/11/10 22:07:46 drahn Exp $

PROG=		traceroute6
MAN=		traceroute6.8
BINOWN=		root
BINGRP=		bin
BINMODE=	4555

CPPFLAGS+=	-DINET6 -DHAVE_POLL

LDSTATIC=	-static

.include <bsd.prog.mk>
