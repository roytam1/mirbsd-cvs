# $MirOS: src/sbin/routed/Makefile,v 1.2 2005/03/15 19:03:56 tg Exp $
# $OpenBSD: Makefile,v 1.15 2004/04/25 16:28:32 itojun Exp $

PROG=		routed
SRCS=		if.c input.c main.c output.c parms.c radix.c rdisc.c \
		table.c trace.c
MAN=		routed.8
CPPFLAGS+=	-D_ROUTED -D'min(a,b)=(a < b ? a : b)' -D'log=syslog'
CPPFLAGS+=	-D'panic(s)={log(LOG_ERR, "%s", s); exit(1);}'

SUBDIR+=	rtquery

# Do *NOT* turn this flag on unless you like security holes
#CPPFLAGS+=	-DPERMIT_TRACE

.include <bsd.prog.mk>
