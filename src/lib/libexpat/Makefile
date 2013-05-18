# $MirOS: src/lib/libexpat/Makefile,v 1.2 2005/10/21 11:02:44 tg Exp $
# $OpenBSD: Makefile,v 1.2 2004/09/22 21:37:35 espie Exp $

SHLIB_VERSION?= 5.0
LIB=		expat
.PATH: ${.CURDIR}/lib
SRCS=		xmlparse.c xmltok.c xmlrole.c
HDRS=		expat.h expat_external.h

.include <bsd.own.mk>
COPTS+=		-Wall
CPPFLAGS+=	-DHAVE_EXPAT_CONFIG_H

includes:
.for _i in ${HDRS}
	@cmp -s ${DESTDIR}/usr/include/${_i} ${.CURDIR}/lib/${_i} \
	    || ${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} \
	    -m ${NONBINMODE} ${.CURDIR}/lib/${_i} ${DESTDIR}/usr/include/
.endfor

.include <bsd.lib.mk>
