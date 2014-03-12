# $MirOS: src/sbin/init/Makefile,v 1.3 2008/03/27 19:05:16 tg Exp $
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
CPPFLAGS+=	-I${BSDSRCDIR:Q}/lib/libc/include

.include <bsd.prog.mk>
