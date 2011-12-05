# $MirOS: gcc/gpcdoc/Makefile,v 1.1 2005/11/20 13:50:43 tg Exp $

FILES!=		echo *.info

all clean cleandir depend includes install lint obj prereq tags:

install:
.for _i in ${FILES}
	${INSTALL} ${INSTALL_COPY} -o ${MANOWN} -g ${MANGRP} -m ${MANMODE} \
	    ${_i} ${DESTDIR}${GCC_INFODIR}/
.endfor

.include <bsd.own.mk>
