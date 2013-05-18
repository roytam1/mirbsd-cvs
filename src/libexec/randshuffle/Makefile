# $MirOS$

SCRIPTS=	randshuffle
NOOBJ=		Yes
NOMAN=		Yes

realinstall:
	cd ${.CURDIR}; install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${SCRIPTS} ${DESTDIR}${BINDIR}/

.include <bsd.prog.mk>
