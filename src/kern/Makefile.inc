# $MirOS$

.ifndef _KERNBASE_MAKEFILE_INC
_KERNBASE_MAKEFILE_INC=	#defined

.ifdef SMALL
CPPFLAGS+=	-DSMALL
.endif

.endif
