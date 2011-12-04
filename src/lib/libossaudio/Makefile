# $MirOS$
# $OpenBSD: Makefile,v 1.2 1998/05/04 06:02:37 deraadt Exp $
# $NetBSD: Makefile,v 1.5 1998/04/13 14:18:45 lukem Exp $

SHLIB_VERSION?=	4.0
LIB=		ossaudio
MAN=		ossaudio.3
SRCS=		ossaudio.c

includes:
	@cd ${.CURDIR}; cmp -s soundcard.h ${DESTDIR}/usr/include/soundcard.h || \
	  ${INSTALL} ${INSTALL_COPY} -m 444 -o $(BINOWN) -g $(BINGRP) soundcard.h \
	  ${DESTDIR}/usr/include

.include <bsd.lib.mk>
