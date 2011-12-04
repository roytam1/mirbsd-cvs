# $MirOS: gcc/Makefile.inc,v 1.5 2005/04/26 05:53:04 tg Exp $

.ifndef _MODGCC_MAKEFILE_INC
_MODGCC_MAKEFILE_INC=1

.if ${MACHINE} == "i386"
NO_ADA=		No
NO_CXX=		No
NO_OBJC=	No
NO_JAVA=	No
NO_PASCAL=	No
.elif ${MACHINE} == "macppc"
NO_ADA=		Yes
NO_CXX=		Yes
NO_OBJC=	Yes
NO_JAVA=	Yes
NO_PASCAL=	Yes
.else
NO_ADA=		Yes
NO_CXX=		Yes
NO_OBJC=	Yes
NO_JAVA=	Yes
NO_PASCAL=	Yes
.endif

.if defined(NO_CXX) && ${NO_CXX:L} != "no"
NO_JAVA=	Yes #implied
.endif

GMAKE?=		/usr/local/bin/gmake

.endif
