# $MirOS: gcc/gpcdoc/Makefile,v 1.3 2005/11/22 22:04:01 tg Exp $

MAN=		gpc.1 gpc-run.1

.PATH: ${.CURDIR}/../gcc/p/doc/en
.PATH: ${.CURDIR}/../gcc/p/doc/generated

# this is the old stuff, to be replaced RSN
FILES!=		echo *.info

afterinstall:
.for _i in ${FILES}
	${INSTALL} ${INSTALL_COPY} -o ${MANOWN} -g ${MANGRP} -m ${MANMODE} \
	    ${_i} ${DESTDIR}${GCC_INFODIR}/
.endfor

.include <bsd.prog.mk>
