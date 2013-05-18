# $MirOS: src/usr.bin/m4/Makefile,v 1.2 2005/03/15 19:23:53 tg Exp $
# $OpenBSD: Makefile,v 1.11 2004/05/12 21:17:03 espie Exp $

# -DEXTENDED
# 	if you want the paste & spaste macros.

PROG=		m4
SRCS=		eval.c expr.c gnum4.c look.c main.c misc.c parser.y \
		tokenizer.l trace.c
CPPFLAGS+=	-DEXTENDED -I.
CDIAGFLAGS=	-Wextra -Wall -Wstrict-prototypes -pedantic \
		-Wno-unused -Wno-char-subscripts -Wno-sign-compare
LDADD+=		-ly -ll
DPADD+=		${LIBY} ${LIBL}

.include <bsd.prog.mk>
