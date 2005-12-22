# $MirOS$
# @(#)Makefile	5.7 (Berkeley) 7/20/92

MAN=	roffbib.1

beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/indxbib.sh ${DESTDIR}${BINDIR}/indxbib
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/roffbib.sh ${DESTDIR}${BINDIR}/roffbib

.include <bsd.prog.mk>
