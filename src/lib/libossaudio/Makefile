# $MirOS: src/lib/libossaudio/Makefile,v 1.3 2005/06/14 13:12:57 tg Exp $
# $OpenBSD: Makefile,v 1.2 1998/05/04 06:02:37 deraadt Exp $
# $NetBSD: Makefile,v 1.5 1998/04/13 14:18:45 lukem Exp $

LIB=		ossaudio
MAN=		ossaudio.3
SRCS=		ossaudio.c
NOPIC=		Yes

.include <bsd.own.mk>
COPTS+=		${PICFLAG}

includes:
	@cd ${.CURDIR} && cmp -s soundcard.h \
	    ${DESTDIR}/usr/include/soundcard.h || ${INSTALL} ${INSTALL_COPY} \
	    -m ${NONBINMODE} -o $(BINOWN) -g $(BINGRP) \
	    soundcard.h ${DESTDIR}/usr/include/

.include <bsd.lib.mk>
