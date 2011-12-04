# $MirOS: src/lib/libedit/TEST/Makefile,v 1.3 2005/04/19 15:16:20 tg Exp $
# $OpenBSD: Makefile,v 1.1 2003/11/25 20:12:39 otto Exp $
# $NetBSD: Makefile,v 1.1 2003/10/16 21:41:46 christos Exp $

NOMAN=		yes
PROG=		test
LDADD+=		-ledit -ltermcap
DPADD+=		${LIBEDIT} ${LIBTERMCAP}

.include <bsd.own.mk>
CPPFLAGS=	-I${.CURDIR}/..
COPTS+=		-Wall

.include <bsd.prog.mk>
