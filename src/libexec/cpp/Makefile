# $MirOS: src/libexec/cpp/Makefile,v 1.6 2008/11/22 13:06:42 tg Exp $
# @(#)Makefile	5.2 (Berkeley) 5/12/90

PROG=		cpp
SRCS=		cpp.c cpy.y
NOMAN=		yes

.include <bsd.own.mk>

CPPFLAGS+=	-Dunix -DFLEXNAMES
COPTS+=		-std=gnu89

#XXX for now
afterinstall:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/xcpp.sh ${DESTDIR}/usr/bin/cpp

.include <bsd.prog.mk>
