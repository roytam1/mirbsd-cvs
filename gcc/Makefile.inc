# $MirOS: gcc/Makefile.inc,v 1.6 2005/05/01 02:51:33 tg Exp $

.ifndef _MODGCC_MAKEFILE_INC
_MODGCC_MAKEFILE_INC=1

.if ${MACHINE} == "i386"
NO_ADA?=	No
NO_CXX?=	No
NO_OBJC?=	No
NO_JAVA?=	No
NO_PASCAL?=	No
NO_THREADS?=	No	# mainly needed for gcj
.elif ${MACHINE} == "macppc"
NO_ADA?=	Yes
NO_CXX?=	Yes
NO_OBJC?=	Yes
NO_JAVA?=	Yes
NO_PASCAL?=	Yes
NO_THREADS?=	Yes
.else
NO_ADA?=	Yes
NO_CXX?=	Yes
NO_OBJC?=	Yes
NO_JAVA=	Yes
NO_PASCAL?=	Yes
NO_THREADS=	Yes
.endif

.if defined(NO_CXX) && ${NO_CXX:L} != "no"
NO_JAVA=	Yes #implied
.endif

GMAKE?=		/usr/local/bin/gmake

LIBGCJ_DEBUG?=	No

.endif
