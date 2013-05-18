# $MirOS: src/usr.sbin/adduser/Makefile,v 1.3 2006/07/08 21:42:56 tg Exp $

SCRIPTS=	adduser
MAN=		adduser.8

realinstall:
	cd ${.CURDIR} && ${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} \
	    -m ${BINMODE} ${SCRIPTS} ${DESTDIR}${BINDIR}/

.include <bsd.prog.mk>
