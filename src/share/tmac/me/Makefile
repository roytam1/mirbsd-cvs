# $MirOS$
# $OpenBSD: Makefile,v 1.4 2003/04/08 01:44:59 millert Exp $
# @(#)Makefile	8.1 (Berkeley) 6/8/93

MSRCS=	acm.me chars.me deltext.me eqn.me float.me footnote.me \
	index.me letterhead.me local.me null.me refer.me sh.me \
	tbl.me thesis.me summary.external
BINDIR=	/usr/share/tmac/me
MAN=	me.7

STRIP_SED=	${.CURDIR}/../strip.sed

all clean cleandir depend lint tags:

beforeinstall:
	cd ${.CURDIR} && for i in ${MSRCS}; do \
		sed -f ${STRIP_SED} <$$i >${DESTDIR}${BINDIR}/$$i; \
		chown ${BINOWN}:${BINGRP} ${DESTDIR}${BINDIR}/$$i; \
		chmod ${SHAREMODE} ${DESTDIR}${BINDIR}/$$i; \
	done

.include <bsd.prog.mk>
