# $MirOS: src/usr.bin/oldroff/neqn/Makefile,v 1.2 2005/04/11 21:21:05 tg Exp $
# @(#)Makefile	5.7 (Berkeley) 1/14/91

PROG=		neqn
CPPFLAGS+=	-I. -DNEQN
SRCS=		diacrit.c eqnbox.c font.c fromto.c funny.c glob.c integral.c \
		io.c lex.c lookup.c mark.c matrix.c move.c over.c paren.c \
		pile.c shift.c size.c sqrt.c text.c ey.y
MACROS=		-mdoc.old
MAN=		neqn.1eqn

.include <bsd.prog.mk>
