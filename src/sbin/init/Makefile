# $MirOS: src/sbin/init/Makefile,v 1.4 2014/03/12 23:11:23 tg Exp $
# $OpenBSD: Makefile,v 1.7 2002/06/09 08:13:06 todd Exp $

STATIC=		-static
BINDIR=		/sbin
BINOWN=		root
BINGRP=		bin
BINMODE=	0500

PROG=		init
MAN=		init.8
DPADD+=		${LIBUTIL}
LDADD+=		-lutil
INSTALLFLAGS=	-fschg
CPPFLAGS+=	-DDEBUGSHELL -DSECURE -DLOGIN_CAP

.include <bsd.prog.mk>
