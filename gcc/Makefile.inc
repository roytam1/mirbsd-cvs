# $MirOS: gcc/Makefile.inc,v 1.3 2005/03/25 21:57:10 tg Exp $

.ifndef _MODGCC_MAKEFILE_INC
_MODGCC_MAKEFILE_INC=1

#NO_ADA=	defined
#NO_CXX=	defined
#NO_OBJC=	defined
NO_JAVA=	defined
#NO_PASCAL=	defined

.ifdef NO_CXX
NO_JAVA=	implied
.endif

GMAKE?=		/usr/local/bin/gmake

.endif
