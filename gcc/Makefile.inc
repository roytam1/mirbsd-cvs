# $MirOS$

.ifndef _MODGCC_MAKEFILE_INC
_MODGCC_MAKEFILE_INC=1

#NO_ADA=	defined
NO_CXX=		defined
NO_OBJC=	defined
NO_JAVA=	defined

.ifdef NO_CXX
NO_JAVA=	implied
.endif

GMAKE?=		/usr/local/bin/gmake

.endif
