# $MirOS: src/bin/sh/Makefile,v 1.5 2005/07/23 20:07:45 tg Exp $
# $NetBSD: Makefile,v 1.80 2005/06/26 19:10:49 christos Exp $

PROG=		sh
SRCS=		alias.c arith.y arith_lex.l builtins.c cd.c echo.c error.c \
		eval.c exec.c expand.c init.c input.c jobs.c kill.c main.c \
		memalloc.c miscbltin.c mystring.c nodes.c options.c output.c \
		parser.c printf.c redir.c syntax.c test.c trap.c var.c
CPPFLAGS+=	-DSHELL
LFLAGS=		-8
CLEANFILES+=	arith.c arith.h arith_lex.c
DPADD+=		${LIBL}
LDADD+=		-ll

CFLAGS_arith_lex.o= -Wno-old-style-definition -Wno-missing-noreturn

.include <bsd.own.mk>
.PATH: ${BSDSRCDIR}/bin/echo ${BSDSRCDIR}/bin/kill ${BSDSRCDIR}/usr.bin/printf

arith.c arith.h: arith.y
	${YACC} -d $>
	mv y.tab.c arith.c
	mv y.tab.h arith.h

.depend: arith.c arith_lex.c

.include <bsd.prog.mk>
