# $MirOS: src/usr.bin/dc/Makefile,v 1.2 2005/03/13 18:32:51 tg Exp $
# $OpenBSD: Makefile,v 1.2 2006/11/26 11:31:09 deraadt Exp $

PROG=	dc
SRCS=	dc.c bcode.c inout.c mem.c stack.c
CFLAGS+= -Wall
LDADD=	-lcrypto
DPADD=	${LIBCRYPTO}

.if make(install)
SUBDIR+= USD.doc
.endif

.include <bsd.prog.mk>
