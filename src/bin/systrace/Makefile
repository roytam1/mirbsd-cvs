# $MirOS: src/bin/systrace/Makefile,v 1.4 2005/10/21 11:02:38 tg Exp $
# $OpenBSD: Makefile,v 1.15 2006/07/02 12:34:15 sturm Exp $

PROG=		systrace
CPPFLAGS+=	-I. -DYY_NO_UNPUT -I${.CURDIR}/../../sys
DPADD+=		${LIBEVENT}
LDADD+=		-levent
CLEANFILES+=	parse.c lex.c y.tab.h

.include <bsd.own.mk>
COPTS+=		-Wall -Wstrict-prototypes -Wmissing-prototypes \
		-Wpointer-arith -Wno-uninitialized

SRCS=	cradle.c filter.c intercept-translate.c intercept.c \
	linux-translate.c openbsd-syscalls.c util.c \
	policy.c systrace-errno.h systrace-error.c \
	systrace-translate.c systrace.c alias.c register.c \
	parse.y lex.l

.include <bsd.prog.mk>
