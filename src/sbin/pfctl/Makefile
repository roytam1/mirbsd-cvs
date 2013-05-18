# $MirOS: src/sbin/pfctl/Makefile,v 1.3 2005/12/19 20:05:53 tg Exp $
# $OpenBSD: Makefile,v 1.15 2004/03/10 18:49:49 mcbride Exp $

PROG=	pfctl
SRCS=	pfctl.c parse.y pfctl_parser.c pf_print_state.c pfctl_altq.c
SRCS+=	pfctl_osfp.c pfctl_radix.c pfctl_table.c pfctl_qstats.c
CFLAGS+= -Wall -Wmissing-prototypes -Wno-uninitialized
CFLAGS+= -Wstrict-prototypes
YFLAGS=
MAN=	pfctl.8

LDADD+=	-lm
DPADD+=	${LIBM}

.include <bsd.prog.mk>
