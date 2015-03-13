# $MirOS$

SCRIPTS=	wtf
MAN=		wtf.1

NROFF=		nrcon -u ${MACROS} ${PAGES}

realinstall:
	cd ${.CURDIR}; install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${SCRIPTS} ${DESTDIR}${BINDIR}/

.include <bsd.prog.mk>
