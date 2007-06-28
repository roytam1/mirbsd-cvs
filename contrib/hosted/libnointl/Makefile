# $MirOS: contrib/hosted/libnointl/Makefile,v 1.2 2007/06/25 16:55:44 tg Exp $
#-
# Makefile for libnointl, a plug-compatible replacement for
# libintl from GNU gettext 0.10.40 and 0.16.1, reverse-engineered.

LIB?=		nointl		# use "intl" to fake
SHLIB_VERSION?=	1.0		# fake gettext 0.10.40
SRCS=		nointl.c
CPPFLAGS+=	-I${.CURDIR}
HDRS=		libintl.h
NOMAN=		Yes

.include <bsd.own.mk>

# fake gettext 0.16.1
#SHLIB_VERSION=	8.0
#.if ${RTLD_TYPE} == "GNU"
#SHLIB_SONAME=	lib${LIB}.so.${SHLIB_VERSION}.1
#.endif

.if (${RTLD_TYPE} == "GNU") || (${RTLD_TYPE} == "BSD")
all: lib${LIB}.la
CLEANFILES+=	lib${LIB}.la

lib${LIB}.la: nointl.la
	sed -e 's!@dlname@!${lt_dlname}!g' \
	    -e 's!@libnames@!${lt_libnames}!g' \
	    -e 's!@statlib@!${lt_statlib}!g' \
	    -e 's!@LIBDIR@!${LIBDIR}!g' \
	    -e 's!@current@!${lt_current}!g' \
	    -e 's!@age@!${lt_age}!g' \
	    -e 's!@revision@!${lt_revision}!g' \
	    <$> >$@

afterinstall:
	${INSTALL} ${INSTALL_COPY} -o ${LIBOWN} -g ${LIBGRP} -m ${SHAREMODE} \
	    lib${LIB}.la ${DESTDIR}${LIBDIR}/
.endif

.include <bsd.lib.mk>

.if ${RTLD_TYPE} == "GNU"
lt_dlname=	lib${LIB}.so.${SHLIB_VERSION:R}
lt_libnames=	${SHLIB_SONAME} lib${LIB}.so.${SHLIB_VERSION:R} lib${LIB}.so
lt_revision=	${SHLIB_SONAME:E}
.else
lt_dlname=	${SHLIB_SONAME}
lt_libnames=	${SHLIB_SONAME}
.endif
lt_current!=	print $$((${SHLIB_VERSION:R} + ${SHLIB_VERSION:E}))
lt_age=		${SHLIB_VERSION:E}
lt_revision?=	0
.if ${_LIBS_STATIC:L} == "yes"
lt_statlib=	lib${LIB}.a
.else
lt_statlib=
.endif
