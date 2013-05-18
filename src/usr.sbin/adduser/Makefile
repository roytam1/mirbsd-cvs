# $MirOS$

SCRIPTS=	adduser
NOMAN=		yes
NOOBJ=		yes

realinstall:
	cd ${.CURDIR} && ${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} \
	    -m ${BINMODE} ${SCRIPTS} ${DESTDIR}${BINDIR}/

.include <bsd.prog.mk>
