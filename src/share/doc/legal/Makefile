# $MirOS$

BINDIR=	${DOCDIR}/legal

FILES=	1stREAD COPYING-1 COPYING-2 COPYING.LIB-2 COPYING.LIB-2_1 \
	LICENCE LICENCE-GNU
NOPROG=	Yes
NOMAN=	Yes
GENFS=	LICENCE-BSD
ROFFS=	lbsd.mdoc lbsd-adv.mdoc lbsd-ansi.mdoc lbsd-caldera.mdoc \
	lbsd-darpa.mdoc lbsd-ieee.mdoc lbsd-ucb.mdoc
MACROS=	-mdoc
CLEANFILES+= ${GENFS}

all: ${GENFS}

LICENCE-BSD: ${ROFFS}
	( cd ${.CURDIR} && ${NROFF} ${.CURDIR}/lbsd.mdoc ) \
	    | col -b >$@ || (rm -f $@; false)

beforeinstall:
	cd ${.CURDIR} && install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} \
	    ${FILES} ${DESTDIR}${BINDIR}/
	install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} LICENCE-BSD \
	    ${DESTDIR}${BINDIR}/LICENCE-BSD 

.include <bsd.prog.mk>
