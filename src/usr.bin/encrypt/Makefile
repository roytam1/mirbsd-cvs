# $MirOS: src/usr.bin/encrypt/Makefile,v 1.6 2009/03/29 13:04:22 tg Exp $
# $OpenBSD: Makefile,v 1.7 2002/06/27 19:56:03 art Exp $

PROG=		encrypt

LDADD+=		-lutil
DPADD+=		${LIBUTIL}
LIBEXEC?=	/usr/libexec
LINKS=		${BINDIR}/encrypt ${LIBEXEC}/makekey
MLINKS=		encrypt.1 makekey.8

LDSTATIC=	-static

.include <bsd.prog.mk>
