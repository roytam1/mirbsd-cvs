# $MirOS$
# $OpenBSD: Makefile,v 1.11 2004/05/12 21:17:03 espie Exp $

# -DEXTENDED 
# 	if you want the paste & spaste macros.

PROG=		m4
SRCS=		eval.c expr.c gnum4.c look.c main.c misc.c parser.y \
		tokenizer.l trace.c
CPPFLAGS+=	-DEXTENDED -I.
CDIAGFLAGS=	-Wextra -Wall -Wstrict-prototypes -pedantic \
		-Wno-unused -Wno-char-subscripts -Wno-sign-compare
CLEANFILES+=	parser.c parser.h tokenizer.o
LDADD+=		-ly -ll
DPADD+=		${LIBY} ${LIBL}

parser.c parser.h: parser.y
	${YACC} -d ${.ALLSRC} && mv y.tab.c parser.c && mv y.tab.h parser.h

tokenizer.o: parser.h

.include <bsd.prog.mk>
