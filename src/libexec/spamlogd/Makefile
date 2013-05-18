# $MirOS: src/libexec/spamlogd/Makefile,v 1.3 2005/11/23 16:04:03 tg Exp $
# $OpenBSD: Makefile,v 1.6 2007/03/04 03:19:41 beck Exp $

PROG=	spamlogd
SRCS=	spamlogd.c sync.c
MAN=	spamlogd.8

CFLAGS+=	-Wall -Wstrict-prototypes
CPPFLAGS+=	-I${.CURDIR}/../spamd

DPADD+=		${LIBPCAP} ${LIBCRYPTO}
LDADD+=		-lpcap -lcrypto

.PATH: ${.CURDIR}/../spamd

.include <bsd.prog.mk>
