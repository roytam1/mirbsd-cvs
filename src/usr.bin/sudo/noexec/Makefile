# $MirOS: src/usr.bin/sudo/noexec/Makefile,v 1.3 2005/04/10 20:33:09 tg Exp $
# $OpenBSD: Makefile,v 1.1 2004/09/28 15:10:51 millert Exp $

.PATH:		${.CURDIR}/..

LIB=		noexec
NOMAN=		yes
SRCS=		sudo_noexec.c
LIBDIR=		/usr/libexec

DEBUGLIBS=	no
SHLIB_SONAME=	libsudo_noexec.so
CLEANFILES+=	${SHLIB_SONAME}

install:
	${INSTALL} ${INSTALL_COPY} -o ${LIBOWN} -g ${LIBGRP} -m ${LIBMODE} \
	    ${SHLIB_SONAME} ${DESTDIR}${LIBDIR}/sudo_noexec.so

.include <bsd.lib.mk>
