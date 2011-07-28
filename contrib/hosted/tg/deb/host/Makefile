# $MirOS: src/usr.bin/host/Makefile,v 1.2 2010/06/08 08:38:29 tg Exp $

PROG=		host
CFLAGS+=	-Wall

.ifdef DEBIAN
CPPFLAGS+=	-DUSE_LIBBSD
LDADD+=		-lbsd -lresolv
.endif

.include <bsd.prog.mk>
