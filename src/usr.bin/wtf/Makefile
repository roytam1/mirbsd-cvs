# $MirOS: src/usr.bin/wtf/Makefile,v 1.3 2015/03/13 21:18:21 tg Exp $

SCRIPTS=	wtf
MAN=		wtf.1

realinstall:
	cd ${.CURDIR}; install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${SCRIPTS} ${DESTDIR}${BINDIR}/

.include <bsd.prog.mk>
