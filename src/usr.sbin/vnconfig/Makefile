# $MirOS: src/usr.sbin/vnconfig/Makefile,v 1.6 2008/03/27 14:53:25 tg Exp $
# $OpenBSD: Makefile,v 1.3 1997/09/21 11:44:35 deraadt Exp $

PROG=		vnconfig
MAN=		vnconfig.8
DPADD+=		${LIBUTIL}
LDADD+=		-lutil

.if defined(SMALL) && ${SMALL:L} != "no"
CPPFLAGS+=	-DSMALL
.else
DPADD+=		${LIBCRYPTO}
LDADD+=		-lcrypto
.endif

LDSTATIC=	-static

.include <bsd.prog.mk>
