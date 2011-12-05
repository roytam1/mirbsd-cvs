# $MirOS: gcc/Makefile.inc,v 1.14 2005/11/22 17:55:18 tg Exp $

.ifndef _MODGCC_MAKEFILE_INC
_MODGCC_MAKEFILE_INC=1

.if ${OStype} == "MirBSD"
.  if ${MACHINE} == "i386"
NO_ADA?=	No
NO_CXX?=	No
NO_OBJC?=	No
NO_JAVA?=	No
NO_PASCAL?=	No
NO_THREADS?=	No	# mainly needed for gcj
.  elif ${MACHINE} == "macppc"
NO_ADA?=	Yes
NO_CXX?=	Yes
NO_OBJC?=	Yes
NO_JAVA?=	Yes
NO_PASCAL?=	Yes
NO_THREADS?=	Yes
.  else
NO_ADA?=	Yes
NO_CXX?=	Yes
NO_OBJC?=	Yes
NO_JAVA=	Yes
NO_PASCAL?=	Yes
NO_THREADS=	Yes
.  endif
.else
GCC_NATIVE=	No
NO_ADA?=	Yes
NO_JAVA=	Yes
NO_THREADS=	Yes
OBJC_GC=	--disable-objc-gc
NO_BOEHMGC=	Yes
.  if ${OStype} == "Darwin"
GMAKE?=		/usr/bin/make
.  endif
.endif

.if defined(NO_CXX) && ${NO_CXX:L} != "no"
NO_JAVA=	Yes #implied
.endif

.if defined(NO_OBJC) && defined(NO_JAVA) \
    && ${NO_OBJC:L} != "no" && ${NO_JAVA:L} != "no"
NO_BOEHMGC=	Yes
.endif

GCC_NATIVE?=	Yes
OBJC_GC?=	--enable-objc-gc
NO_BOEHMGC?=	No
GMAKE?=		/usr/local/bin/gmake

# System defines
GCCVERSION=	3.4.5
LIBGCC_REV=	1.1
# XXX how about automatically deriving these below?
LIBGCJ_REV=	5.0
LIBOBJC_REV=	3.1
LIBOBJC_VER=	4:0:1
LIBCXX_REV=	37.0
LIBCXX_VER=	37:0:0

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

.endif
