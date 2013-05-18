# $MirOS$

SCRIPTS=	brainfuck
MAN=		brainfuck.1

realinstall:
	cd ${.CURDIR}; install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${SCRIPTS} ${DESTDIR}${BINDIR}/

.include <bsd.prog.mk>
