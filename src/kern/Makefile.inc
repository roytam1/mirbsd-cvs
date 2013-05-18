# $MirOS: src/kern/Makefile.inc,v 1.1 2007/02/05 23:48:02 tg Exp $

.ifndef _KERNBASE_MAKEFILE_INC
_KERNBASE_MAKEFILE_INC=	#defined

.ifdef SMALL
CPPFLAGS+=	-DSMALL
.endif

.ifdef KERNNOGCC
CPPFLAGS+=	-D_KERN_HOSTED
.endif

.endif
