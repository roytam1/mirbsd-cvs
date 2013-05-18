#	$OpenBSD: Makefile,v 1.4 1997/04/27 20:56:59 millert Exp $
#	$NetBSD: Makefile,v 1.2 1995/07/03 21:25:05 cgd Exp $

LIBS=	llib-lposix.ln llib-lstdc.ln

all:	${LIBS}

install:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${LIBS} ${DESTDIR}${LINTLIBDIR}

clean cleanall:
	rm -f ${LIBS}

llib-lposix.ln: llib-lposix
	CC=${_ORIG_CC:Q} lint -Cposix ${.ALLSRC}

llib-lstdc.ln: llib-lstdc
	CC=${_ORIG_CC:Q} lint -Cstdc ${.ALLSRC}

.include <bsd.prog.mk>
