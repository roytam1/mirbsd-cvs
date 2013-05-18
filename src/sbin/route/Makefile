# $MirOS: src/sbin/route/Makefile,v 1.5 2005/12/05 16:06:06 tg Exp $
# $OpenBSD: Makefile,v 1.9 2005/03/30 06:02:52 henning Exp $

PROG=	route
MAN=	route.8
SRCS=	route.c show.c

afterinstall:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/route_print.sh ${DESTDIR}/usr/bin/route_print

.include <bsd.prog.mk>
