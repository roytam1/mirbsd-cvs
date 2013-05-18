# $MirOS: src/kern/Makefile.inc,v 1.4 2008/08/01 14:43:45 tg Exp $

.ifndef _KERNBASE_MAKEFILE_INC
_KERNBASE_MAKEFILE_INC=	#defined

.if ${CPPFLAGS:N1:S-I${KERNBASE}/include1:M1} == ""
CPPFLAGS+=	-I${KERNBASE}/include
.endif

.ifdef SMALL
CPPFLAGS+=	-DSMALL
.endif

.ifdef KERNNOGCC
CPPFLAGS+=	-D_KERN_HOSTED
.endif

.endif
