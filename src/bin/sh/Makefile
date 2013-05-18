# $MirOS: src/bin/sh/Makefile,v 1.8 2006/07/21 21:39:37 tg Exp $
# $NetBSD: Makefile,v 1.80 2005/06/26 19:10:49 christos Exp $

PROG=		nbsh
SRCS=		alias.c arith.y arith_lex.l builtins.c cd.c echo.c error.c \
		eval.c exec.c expand.c init.c input.c jobs.c kill.c main.c \
		memalloc.c miscbltin.c mystring.c nodes.c options.c output.c \
		parser.c printf.c redir.c syntax.c test.c trap.c var.c
CPPFLAGS+=	-DSHELL
LFLAGS=		-8
CLEANFILES+=	arith.c arith.h arith_lex.c
DPADD+=		${LIBL}
LDADD+=		-ll

CLEANFILES+=	${PROG}.1
#LINKS+=	${BINDIR}/${PROG} ${BINDIR}/sh
#MLINKS+=	${PROG}.1 sh.1

CFLAGS_arith_lex.o= -Wno-old-style-definition -Wno-missing-noreturn

.include <bsd.own.mk>
.PATH: ${BSDSRCDIR}/bin/echo ${BSDSRCDIR}/bin/kill ${BSDSRCDIR}/usr.bin/printf

arith.c arith.h: arith.y
	${YACC} -d $>
	mv y.tab.c arith.c
	mv y.tab.h arith.h

.depend: arith.c arith_lex.c

${PROG}.1: ${.CURDIR}/sh.1
	cp $> $@

.include <bsd.prog.mk>
