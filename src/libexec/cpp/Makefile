# $MirOS: src/libexec/cpp/Makefile,v 1.4 2007/08/24 14:20:04 tg Exp $
# @(#)Makefile	5.2 (Berkeley) 5/12/90

PROG=		cpp
SRCS=		cpp.c cpy.y
NOMAN=		yes

.include <bsd.own.mk>

CPPFLAGS+=	-Dunix=1 -DFLEXNAMES
COPTS+=		-std=gnu89
YFLAGS=

afterinstall:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/xcpp.sh ${DESTDIR}/usr/bin/cpp

.include <bsd.prog.mk>
