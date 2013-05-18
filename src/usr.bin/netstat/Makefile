# $MirOS$
# $OpenBSD: Makefile,v 1.12 2004/06/25 20:05:40 henning Exp $

PROG=	netstat
SRCS=	if.c inet.c inet6.c ipx.c main.c mbuf.c mroute.c route.c \
	unix.c atalk.c mroute6.c
BINGRP=	kmem
BINMODE=2555
LDADD=	-lkvm -lz
DPADD=	${LIBKVM} ${LIBZ}
INET6?=	yes

CPPFLAGS+=	-DINET6

.include <bsd.prog.mk>
