# $MirOS$
# $NetBSD: Makefile,v 1.1 2003/06/27 08:40:59 tshiozak Exp $

NOOBJ=	Yes
FILES=

BINDIR?= /usr/share/i18n/iconv

FILES+= iconv.dir
FILESDIR= ${BINDIR}

afterinstall:
	cd ${.CURDIR} && ${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} \
	    -m ${BINMODE} ${FILES} ${DESTDIR}${FILESDIR}/

.include <bsd.prog.mk>
