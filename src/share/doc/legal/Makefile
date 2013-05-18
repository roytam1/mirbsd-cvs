# $MirOS: src/share/doc/legal/Makefile,v 1.8 2009/06/29 17:55:18 tg Exp $

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
CLEANFILES+=	${GENFS} grml.0 grml bsd4me.0 bsd4me

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

bsd4me.0: ${ROFFS}
	( cd ${.CURDIR} && ${NROFF} -rg2 ${.CURDIR}/lbsd.mdoc ) \
	    >$@ || (rm -f $@; false)

bsd4me: bsd4me.0
	col -bx <${.ALLSRC} >$@

beforeinstall:
	cd ${.CURDIR} && install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} \
	    ${FILES} ${DESTDIR}${BINDIR}/
	install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} LICENCE-BSD \
	    ${DESTDIR}${BINDIR}/LICENCE-BSD 

.include <bsd.prog.mk>
