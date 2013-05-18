# $MirOS: src/share/doc/legal/Makefile,v 1.7 2009/01/17 12:50:00 tg Exp $

BINDIR=		${DOCDIR}/legal
NROFF=		nrcon -e ${MACROS} ${PAGES}

FILES=		1stREAD COPYING-1 COPYING-2 COPYING.LIB-2 COPYING.LIB-2_1 \
		LICENCE LICENCE-GNU
NOPROG=		Yes
NOMAN=		Yes
GENFS=		LICENCE-BSD.0 LICENCE-BSD
ROFFS=		lbsd-adc.mdoc lbsd-adv.mdoc lbsd-ansi.mdoc lbsd-caldera.mdoc \
		lbsd-darpa.mdoc lbsd-ieee.mdoc lbsd-ucb.mdoc lbsd.mdoc
MACROS=		-mdoc
CLEANFILES+=	${GENFS} grml.0 grml

all: ${GENFS}

LICENCE-BSD.0: ${ROFFS}
	( cd ${.CURDIR} && ${NROFF} ${.CURDIR}/lbsd.mdoc ) \
	    >$@ || (rm -f $@; false)

LICENCE-BSD: LICENCE-BSD.0
	col -b <${.ALLSRC} >$@

grml.0: ${ROFFS}
	( cd ${.CURDIR} && ${NROFF} -rg1 ${.CURDIR}/lbsd.mdoc ) \
	    >$@ || (rm -f $@; false)

grml: grml.0
	col -bx <${.ALLSRC} >$@

beforeinstall:
	cd ${.CURDIR} && install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} \
	    ${FILES} ${DESTDIR}${BINDIR}/
	install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} LICENCE-BSD \
	    ${DESTDIR}${BINDIR}/LICENCE-BSD 

.include <bsd.prog.mk>
