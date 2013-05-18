# $MirOS: src/usr.bin/encrypt/Makefile,v 1.5 2008/03/27 14:53:24 tg Exp $
# $OpenBSD: Makefile,v 1.7 2002/06/27 19:56:03 art Exp $

PROG=		encrypt
SRCS=		encrypt.c pwd_gensalt.c
.PATH: ${.CURDIR}/../passwd

LDADD+=		-lutil
DPADD+=		${LIBUTIL}
LIBEXEC?=	/usr/libexec
LINKS=		${BINDIR}/encrypt ${LIBEXEC}/makekey
MLINKS=		encrypt.1 makekey.8

LDSTATIC=	-static

.include <bsd.prog.mk>
