# $MirOS: src/sbin/route/Makefile,v 1.3 2005/03/15 19:04:47 tg Exp $
# $OpenBSD: Makefile,v 1.9 2005/03/30 06:02:52 henning Exp $

PROG=	route
MAN=	route.8
SRCS=	route.c show.c

route.o .depend lint tags: keywords.h

afterinstall:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/route_print.sh ${DESTDIR}${BINDIR}/route_print

.include <bsd.prog.mk>
