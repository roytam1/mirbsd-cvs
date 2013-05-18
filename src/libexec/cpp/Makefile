# $MirOS$

PROG=		cpp
SRCS=		cpp.c cpy.y scanner.l
CPPFLAGS+=	-DCPP_DEBUG -I.

# for now
afterinstall:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/xcpp.sh ${DESTDIR}/usr/bin/cpp

.include <bsd.prog.mk>
