# $MirOS$
# $OpenBSD: Makefile,v 1.1 2004/09/28 15:10:51 millert Exp $

.PATH:		${.CURDIR}/..

LIB=	noexec
NOMAN=	yes
SRCS=	sudo_noexec.c
LIBDIR=	/usr/libexec

DEBUGLIBS= no
SHLIB_VERSION=0.0

install:
	${INSTALL} ${INSTALL_COPY} -o ${LIBOWN} -g ${LIBGRP} -m ${LIBMODE} \
	    lib${LIB}.so.${SHLIB_VERSION} \
	    ${DESTDIR}${LIBDIR}/sudo_noexec.so

.include <bsd.lib.mk>
