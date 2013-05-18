# $MirOS: src/kern/Makefile.inc,v 1.3 2007/02/06 18:58:06 tg Exp $

.ifndef _KERNBASE_MAKEFILE_INC
_KERNBASE_MAKEFILE_INC=	#defined

.if !${CPPFLAGS:M-I${KERNBASE}/include}
CPPFLAGS+=	-I${KERNBASE}/include
.endif

.ifdef SMALL
CPPFLAGS+=	-DSMALL
.endif

.ifdef KERNNOGCC
CPPFLAGS+=	-D_KERN_HOSTED
.endif

.endif
