# $MirOS$
# $OpenBSD: Makefile,v 1.4 2003/04/08 01:44:59 millert Exp $
# @(#)Makefile	8.1 (Berkeley) 6/8/93

MSRCS=	doc doc-ditroff doc-common doc-nroff doc-syms
BINDIR=	/usr/share/tmac/mdoc
LINKS=	${BINDIR}/doc ${BINDIR}/../tmac.doc

STRIP_SED=	${.CURDIR}/../strip.sed
NOOBJ=		yes

all clean cleandir depend lint tags:

beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/README \
		${DESTDIR}${BINDIR}/../README.mdoc
	for i in ${MSRCS}; do \
		sed -f ${STRIP_SED} <$$i >${DESTDIR}${BINDIR}/$$i; \
		chown ${BINOWN}:${BINGRP} ${DESTDIR}${BINDIR}/$$i; \
		chmod ${SHAREMODE} ${DESTDIR}${BINDIR}/$$i; \
	done

.PHONY: check check-loud check-silent

check:
	@echo "Type 'make check-loud' or 'make check-silent' to test!"

check-loud:
	@echo "Remember to have done 'sudo make install' first!\n"
	nroff -mandoc ${.CURDIR}/test.5

check-silent:
	@echo "Remember to have done 'sudo make install' first!\n"
	nroff -mandoc ${.CURDIR}/test.5 >/dev/null

.include <bsd.prog.mk>
