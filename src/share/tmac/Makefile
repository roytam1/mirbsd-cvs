# $MirOS: src/share/tmac/Makefile,v 1.2 2005/03/06 19:38:52 tg Exp $
# $OpenBSD: Makefile,v 1.6 2001/07/20 19:44:03 mickey Exp $
# from: @(#)Makefile	6.13 (Berkeley) 3/20/91

FILES=	tmac.andoc tmac.r tmac.s tmac.e
FILES+=	tmac.a tmac.cp tmac.doc.old tmac.sU
FILES+=	tmac.an.old tmac.an.v6compat tmac.an6n tmac.an6t
FILES+=	tmac.bib tmac.m tmac.os tmac.scover

LINKS=	${BINDIR}/tmac/tmac.andoc ${BINDIR}/tmac/tmac.an

.include <bsd.own.mk>

SUBDIR=	mdoc me ms
.if ${CROSS_MODE:L} != "yes"
SUBDIR+=tab
.endif

realinstall:
	cd ${.CURDIR} && install -c -o ${BINOWN} -g ${BINGRP} \
	    -m ${SHAREMODE} ${FILES} ${DESTDIR}${BINDIR}/tmac/

.include <bsd.prog.mk>
