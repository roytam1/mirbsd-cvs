# $MirOS: src/libexec/ld.so/Makefile.inc,v 1.2 2005/11/23 16:03:59 tg Exp $

.include <bsd.own.mk>

COPTS+=		-Wall -Werror
CPPFLAGS+=	-I${.CURDIR}
