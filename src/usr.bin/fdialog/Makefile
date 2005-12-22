# $MirOS$
# $ekkoBSD: Makefile,v 1.10 2003/11/23 21:25:38 dave Exp $

CFLAGS+= 	-Wall -Wmissing-prototypes -Wno-uninitialized \
		-Wstrict-prototypes
CPPFLAGS+=	-I.

LDADD+=		-lcdk -lcurses -ll -ly
DPADD+=		${LIBCDK} ${LIBCURSES} ${LIBL} ${LIBY}

YFLAGS=		-d
#CFLAGS+=	-g -O0
#CPPFLAGS+=	-DFDL_DEBUG

SRCS=		parse.y lexer.l fdialog.c menu_item.c process.c utils.c
PROG=		fdialog

CLEANFILES=	y.tab.h y.tab.c

y.tab.h:	parse.y fdialog.h

beforedepend:
	${YACC} ${YFLAGS} ${.CURDIR}/parse.y

.include <bsd.prog.mk>
