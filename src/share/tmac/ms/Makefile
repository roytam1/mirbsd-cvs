# $MirOS: src/share/tmac/ms/Makefile,v 1.1.7.1 2005/03/06 16:33:42 tg Exp $
# $OpenBSD: Makefile,v 1.4 2003/04/08 01:44:59 millert Exp $
# @(#)Makefile	8.1 (Berkeley) 6/8/93

MSRCS=	acc.ms cov.ms eqn.ms ref.ms tbl.ms ths.ms toc.ms
BINDIR=	/usr/share/tmac/ms

STRIP_SED=	${.CURDIR}/../strip.sed
NOOBJ=		yes

all clean cleandir depend lint tags:

beforeinstall:
	for i in ${MSRCS}; do \
		rm -f ${DESTDIR}${BINDIR}/$$i; \
		sed -f ${STRIP_SED} <$$i >${DESTDIR}${BINDIR}/$$i; \
		chown ${BINOWN}:${BINGRP} ${DESTDIR}${BINDIR}/$$i; \
		chmod ${SHAREMODE} ${DESTDIR}${BINDIR}/$$i; \
	done

.include <bsd.prog.mk>
