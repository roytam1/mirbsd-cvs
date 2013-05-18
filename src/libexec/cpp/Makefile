# $MirOS: src/libexec/cpp/Makefile,v 1.2 2005/03/06 19:23:58 tg Exp $
# @(#)Makefile	5.2 (Berkeley) 5/12/90

PROG=		cpp
SRCS=		cpp.c cpy.y
NOMAN=		yes
CPPFLAGS+=	-Dunix=1 -DFLEXNAMES
YFLAGS=

afterinstall:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/xcpp.sh ${DESTDIR}/usr/bin/cpp

.include <bsd.prog.mk>
