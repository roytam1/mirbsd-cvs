# $MirOS: src/sbin/init/Makefile,v 1.2 2005/03/15 19:03:54 tg Exp $
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
