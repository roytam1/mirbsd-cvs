# $MirOS: gcc/Makefile.inc,v 1.25 2006/11/03 01:14:03 tg Exp $

.ifndef _MODGCC_MAKEFILE_INC
_MODGCC_MAKEFILE_INC=1

.include "Makefile.lang"

.if ${OStype} != "MirBSD"
.  if ${OStype} == "Darwin"
GMAKE?=		/usr/bin/make
.  endif
.endif

GCC_NATIVE?=	Yes
GMAKE?=		/usr/mpkg/bin/gmake
CPP=		${CC} -E

.if ${NO_BOEHMGC:L} != "no"
OBJC_GC=	--disable-objc-gc
.else
OBJC_GC=	--enable-objc-gc
.endif

# System defines
GCCVERSION=	3.4.6
LIBGCC_REV=	2.0
# XXX how about automatically deriving these below?
LIBGCJ_REV=	5.0
LIBOBJC_REV=	3.1
LIBOBJC_VER=	4:0:1
LIBCXX_REV=	39.0
LIBCXX_VER=	39:0:0

.if ${GCC_NATIVE:L} == "yes"
GCC_PREFIX=	/usr
GCC_INFODIR=	/usr/share/info
GCC_MANDIR=	/usr/share/man
.else
PREFIX?=	/usr/local
GCC_PREFIX?=	${PREFIX}
GCC_INFODIR?=	${GCC_PREFIX}/info
GCC_MANDIR?=	${GCC_PREFIX}/man
.endif
MANDIR=		${GCC_MANDIR}/cat

.endif