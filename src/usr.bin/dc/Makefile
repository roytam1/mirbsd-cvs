# $MirOS$
# $OpenBSD: Makefile,v 1.1 2003/09/19 17:58:25 otto Exp $

PROG=	dc
SRCS=	dc.c bcode.c inout.c mem.c stack.c
CFLAGS+= -Wall
LDADD=	-lcrypto

.if make(install)
SUBDIR+= USD.doc
.endif

.include <bsd.prog.mk>
