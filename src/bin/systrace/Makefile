# $MirOS: src/bin/systrace/Makefile,v 1.3 2005/04/26 15:12:25 tg Exp $
# $OpenBSD: Makefile,v 1.13 2004/07/09 21:53:55 mickey Exp $

PROG=		systrace
CPPFLAGS+=	-I. -DYY_NO_UNPUT -I${.CURDIR}/../../sys
DPADD+=		${LIBEVENT}
LDADD+=		-levent
CLEANFILES+=	parse.c lex.c y.tab.h

.include <bsd.own.mk>
COPTS+=		-Wall -Wstrict-prototypes -Wmissing-prototypes \
		-Wpointer-arith -Wno-uninitialized

SRCS=	cradle.c filter.c intercept-translate.c intercept.c \
	openbsd-syscalls.c util.c \
	policy.c systrace-errno.h systrace-error.c \
	systrace-translate.c systrace.c alias.c register.c \
	parse.y lex.l

beforedepend: parse.c lex.c

.include <bsd.prog.mk>
