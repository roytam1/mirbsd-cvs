# $MirOS$
# $OpenBSD: Makefile,v 1.12 2004/01/23 20:51:18 sturm Exp $

PROG=		systrace
CPPFLAGS+=	-I. -DYY_NO_UNPUT
CFLAGS+=	-Wall -Wstrict-prototypes -Wmissing-prototypes \
		-Wpointer-arith -Wno-uninitialized
DPADD+=		${LIBEVENT}
LDADD+=		-levent
CLEANFILES+=	parse.c lex.c y.tab.h

SRCS=	cradle.c filter.c intercept-translate.c intercept.c \
	openbsd-syscalls.c util.c \
	policy.c systrace-errno.h systrace-error.c \
	systrace-translate.c systrace.c alias.c register.c \
	parse.y lex.l

beforedepend: parse.c lex.c

.include <bsd.prog.mk>
