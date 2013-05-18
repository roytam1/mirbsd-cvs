# $MirOS: src/share/tmac/mdoc/Makefile,v 1.3 2005/03/15 16:26:17 tg Exp $
# $OpenBSD: Makefile,v 1.4 2003/04/08 01:44:59 millert Exp $
# @(#)Makefile	8.1 (Berkeley) 6/8/93

MSRCS=	doc doc-ditroff doc-common doc-nroff doc-syms
BINDIR=	/usr/share/tmac/mdoc
LINKS=	${BINDIR}/doc ${BINDIR}/../tmac.doc

STRIP_SED=	${.CURDIR}/../strip.sed
NOOBJ=		yes

all clean cleandir depend lint tags:

beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${SHAREMODE} \
	    ${.CURDIR}/README ${DESTDIR}${BINDIR}/../README.mdoc
	for i in ${MSRCS}; do \
		rm -f ${DESTDIR}${BINDIR}/$$i; \
		sed -f ${STRIP_SED} <$$i >${DESTDIR}${BINDIR}/$$i; \
		chown ${BINOWN}:${BINGRP} ${DESTDIR}${BINDIR}/$$i; \
		chmod ${SHAREMODE} ${DESTDIR}${BINDIR}/$$i; \
	done

.include <bsd.prog.mk>
