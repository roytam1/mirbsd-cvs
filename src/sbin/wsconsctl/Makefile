# $MirOS$
# $OpenBSD: Makefile,v 1.13 2004/01/05 02:55:28 espie Exp $

PROG=	wsconsctl
SRCS=	display.c keyboard.c keysym.c map_parse.y map_scan.l \
	mouse.c util.c wsconsctl.c
MAN=	wsconsctl.8

CPPFLAGS+=	-I.
CLEANFILES+=	keysym.h y.tab.h

beforedepend: keysym.h

keysym.h: mkkeysym.sh ${DESTDIR}/usr/include/dev/wscons/wsksymdef.h
	${SHELL} ${.CURDIR}/mkkeysym.sh \
	  ${DESTDIR}/usr/include/dev/wscons/wsksymdef.h >keysym.h

.include <bsd.prog.mk>
