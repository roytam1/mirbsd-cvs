# $MirOS: src/sbin/route/Makefile,v 1.2 2005/03/06 19:50:34 tg Exp $
# $OpenBSD: Makefile,v 1.6 1999/12/08 07:55:54 itojun Exp $

PROG=	route
MAN=	route.8
SRCS=	route.c show.c keywords.c

CPPFLAGS+=	-DINET6

beforedepend: keywords.h

afterinstall:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/route_print.sh ${DESTDIR}/usr/bin/route_print

.include <bsd.prog.mk>
