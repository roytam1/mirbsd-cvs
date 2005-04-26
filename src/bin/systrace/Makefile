# $MirOS: src/bin/systrace/Makefile,v 1.2 2005/03/15 18:58:32 tg Exp $
# $OpenBSD: Makefile,v 1.13 2004/07/09 21:53:55 mickey Exp $

PROG=		systrace
CPPFLAGS+=	-I. -DYY_NO_UNPUT -I${.CURDIR}/../../sys
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
