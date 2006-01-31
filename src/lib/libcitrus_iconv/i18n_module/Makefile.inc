# $MirOS$
# $NetBSD: Makefile.inc,v 1.8 2004/05/17 05:49:54 lukem Exp $

NOLINT=		# defined
NOPICINSTALL=	# defined
NOPROFILE=	# defined

.include <bsd.own.mk>
.include "../Makefile.inc"

LIBDIR=		/usr/lib/i18n
CPPFLAGS+=	-I${NBLIBC}/citrus
CPPFLAGS+=	-DLIBC_SCCS
BASENAME=	${.CURDIR:T}
LIB=		${BASENAME}
SHLIB_SONAME=	lib${LIB}.so.4.4	# versioned(!) bundle
SRCS_1=		${SRCPRE}${BASENAME}.c
SRCS_2!=	echo '${SRCS_1}' | tr '[:upper:]' '[:lower:]'
SRCS?=		${SRCS_2}

.PATH:	${NBLIBC}/citrus/modules
