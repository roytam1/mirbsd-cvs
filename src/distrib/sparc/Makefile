# $MirOS: src/distrib/sparc/Makefile,v 1.6 2006/07/05 04:47:33 tg Exp $

.include <bsd.own.mk>

REL_NO_GENERIC?=No
REL_NO_RAMDISK?=No

.if make(obj) || make(clean) || make(cleandir) || make(cleannobsd)
_DESCEND=	yes
.else
_DESCEND=	no
.endif

SUBDIR=

.if ${_DESCEND} == "yes" || ${REL_NO_GENERIC:L} != "yes"
SUBDIR+=	../generic
.endif

.if ${_DESCEND} == "yes" || ${REL_NO_RAMDISK:L} != "yes"
SUBDIR+=	../ramdisk
#SUBDIR+=	../miniroot
.endif

cleannobsd: _SUBDIRUSE

unconfig:
	-cd ../ramdisk && ${MAKE} unconfig

.include <bsd.subdir.mk>
