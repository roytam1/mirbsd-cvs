# $MirOS: src/distrib/sparc/Makefile,v 1.4 2006/06/11 01:08:30 tg Exp $

.include <bsd.own.mk>

REL_NO_KERNEL?=	No
.if ${REL_NO_KERNEL:L} != "yes"
REL_NO_GENERIC?=No
REL_NO_RAMDISK?=No
REL_NO_MINIROOT?=No
REL_NO_FLOPPY?=	No
REL_NO_AUTOISO?=No
.else
REL_NO_GENERIC=	Yes
REL_NO_RAMDISK=	Yes
REL_NO_MINIROOT=Yes
REL_NO_FLOPPY=	Yes
REL_NO_AUTOISO=	Yes
.endif

.if ${REL_NO_RAMDISK:L} == "yes"
REL_NO_AUTOISO=	Yes
.endif

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
.endif

.if ${_DESCEND} == "yes" || ${REL_NO_MINIROOT:L} != "yes"
SUBDIR+=	../miniroot
.endif

.if ${_DESCEND} == "yes" || ${REL_NO_AUTOISO:L} != "yes"
SUBDIR+=	cdfs
.endif


cleannobsd: _SUBDIRUSE

unconfig:
	-cd ../ramdisk && ${MAKE} unconfig

.include <bsd.subdir.mk>
