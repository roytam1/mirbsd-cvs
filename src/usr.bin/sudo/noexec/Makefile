# $MirOS: src/usr.bin/sudo/noexec/Makefile,v 1.4 2005/11/23 20:38:24 tg Exp $
# $OpenBSD: Makefile,v 1.1 2004/09/28 15:10:51 millert Exp $

.PATH:		${.CURDIR}/..

LIB=		noexec
NOMAN=		yes
_LIBS_STATIC=	No
SRCS=		sudo_noexec.c
LIBDIR=		/usr/libexec

DEBUGLIBS=	no
SHLIB_SONAME=	libsudo_noexec.so
CLEANFILES+=	${SHLIB_SONAME}

install:
	${INSTALL} ${INSTALL_COPY} -o ${LIBOWN} -g ${LIBGRP} -m ${LIBMODE} \
	    ${SHLIB_SONAME} ${DESTDIR}${LIBDIR}/sudo_noexec.so

.include <bsd.lib.mk>
