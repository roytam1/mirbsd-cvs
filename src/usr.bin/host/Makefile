# $MirOS: src/usr.bin/host/Makefile,v 1.1.7.1 2005/03/06 16:46:48 tg Exp $

PROG=		host
CFLAGS+=	-Wall

.ifdef DEBIAN
CPPFLAGS+=	-DUSE_LIBBSD
LDADD+=		-lbsd -lresolv
.endif

.include <bsd.prog.mk>
