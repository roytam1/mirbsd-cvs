# $MirOS$

NOOBJ=		yes	# for now

afterinstall:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${SHAREMODE} \
	    ${.CURDIR}/bxinst.${MACHINE} ${DESTDIR}/usr/mdec/bootxx.sh

.include <bsd.prog.mk>
