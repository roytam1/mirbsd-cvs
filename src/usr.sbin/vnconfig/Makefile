# $MirOS: src/usr.sbin/vnconfig/Makefile,v 1.2 2006/02/21 23:42:54 tg Exp $
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

.include <bsd.prog.mk>
