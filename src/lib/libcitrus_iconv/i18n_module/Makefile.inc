# $MirOS: src/lib/libcitrus_iconv/i18n_module/Makefile.inc,v 1.5 2006/09/29 21:59:55 tg Exp $
# $NetBSD: Makefile.inc,v 1.8 2004/05/17 05:49:54 lukem Exp $

.include <bsd.own.mk>
.include "../Makefile.inc"

# versioned(!) plugins
.include "shlib_version"
SHLIB_VERSION?=	${major}.${minor}
SHLIB_TYPE=	plugin

LIBDIR=		/usr/lib/i18n
CPPFLAGS+=	-I${NBLIBC}/citrus
CPPFLAGS+=	-DLIBC_SCCS
BASENAME=	${.CURDIR:T}
LIB=		${BASENAME}
SRCS_1=		${SRCPRE}${BASENAME}.c
SRCS_2!=	echo '${SRCS_1}' | tr '[:upper:]' '[:lower:]'
SRCS?=		${SRCS_2}

.PATH:	${NBLIBC}/citrus/modules
