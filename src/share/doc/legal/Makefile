# $MirOS: src/share/doc/legal/Makefile,v 1.2 2005/03/20 18:38:37 tg Exp $

BINDIR=	${DOCDIR}/legal

FILES=	1stREAD COPYING-1 COPYING-2 COPYING.LIB-2 COPYING.LIB-2_1 \
	LICENCE LICENCE-GNU
NOPROG=	Yes
NOMAN=	Yes
GENFS=	LICENCE-BSD.0 LICENCE-BSD
ROFFS=	lbsd-adc.mdoc lbsd-adp.mdoc lbsd-adv.mdoc lbsd-ansi.mdoc \
	lbsd-caldera.mdoc lbsd-darpa.mdoc lbsd-ieee.mdoc \
	lbsd-ucb.mdoc lbsd.mdoc
MACROS=	-mdoc
CLEANFILES+= ${GENFS}

all: ${GENFS}

LICENCE-BSD.0: ${ROFFS}
	( cd ${.CURDIR} && ${NROFF} ${.CURDIR}/lbsd.mdoc ) \
	    >$@ || (rm -f $@; false)

LICENCE-BSD: LICENCE-BSD.0
	col -b <${.ALLSRC} >$@

beforeinstall:
	cd ${.CURDIR} && install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} \
	    ${FILES} ${DESTDIR}${BINDIR}/
	install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} LICENCE-BSD \
	    ${DESTDIR}${BINDIR}/LICENCE-BSD 

.include <bsd.prog.mk>
