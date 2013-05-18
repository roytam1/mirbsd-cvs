# $MirOS: src/usr.bin/encrypt/Makefile,v 1.3 2005/03/15 19:23:49 tg Exp $
# $OpenBSD: Makefile,v 1.7 2002/06/27 19:56:03 art Exp $

PROG=		encrypt
SRCS=		encrypt.c pwd_gensalt.c
.PATH: ${.CURDIR}/../passwd

LDADD+=		-lutil
DPADD+=		${LIBUTIL}
LIBEXEC?=	/usr/libexec
LINKS=		${BINDIR}/encrypt ${LIBEXEC}/makekey
MLINKS=		encrypt.1 makekey.8

.include <bsd.prog.mk>
