# $MirOS$
# $OpenBSD: Makefile,v 1.6 1999/12/08 07:55:54 itojun Exp $

PROG=	route
MAN=	route.8
SRCS=	route.c show.c keywords.c

CPPFLAGS+=	-DINET6

route.o .depend lint tags: keywords.h

afterinstall:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/route_print.sh ${DESTDIR}/usr/bin/route_print

.include <bsd.prog.mk>
