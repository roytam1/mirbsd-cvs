# $MirOS: src/usr.bin/oldroff/neqn/Makefile,v 1.1.7.1 2005/03/06 16:56:02 tg Exp $
# @(#)Makefile	5.7 (Berkeley) 1/14/91

PROG=		neqn
CPPFLAGS+=	-I. -DNEQN
YFLAGS+=	-d
SRCS=		diacrit.c eqnbox.c font.c fromto.c funny.c glob.c integral.c \
		io.c lex.c lookup.c mark.c matrix.c move.c over.c paren.c \
		pile.c shift.c size.c sqrt.c text.c
OBJS+=		e.o

MACROS=		-mdoc.old
MAN=		neqn.1eqn

CLEANFILES+=	e.c e.def y.tab.h

e.c:
	${YACC} ${YFLAGS} ${.CURDIR}/e.y
	mv y.tab.c e.c
	mv y.tab.h e.def

e.def: e.c

beforedepend: e.def

.include <bsd.prog.mk>
