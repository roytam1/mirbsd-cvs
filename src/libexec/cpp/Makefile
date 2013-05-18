# $MirOS: src/libexec/cpp/Makefile,v 1.3 2007/04/28 00:12:45 tg Exp $
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
