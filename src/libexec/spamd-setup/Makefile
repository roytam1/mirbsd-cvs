# $MirOS: src/libexec/spamd-setup/Makefile,v 1.3 2013/08/05 22:06:13 tg Exp $
# $OpenBSD: Makefile,v 1.4 2005/05/24 22:23:04 millert Exp $

PROG=	spamd-setup
SRCS=	spamd-setup.c
MAN=	spamd-setup.8

LDADD=	-lz
DPADD=	${LIBZ}

CFLAGS+= -Wall -Wstrict-prototypes

.include <bsd.prog.mk>
