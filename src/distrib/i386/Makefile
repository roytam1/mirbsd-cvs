# $MirOS: src/distrib/i386/Makefile,v 1.6 2006/04/05 23:14:40 tg Exp $

.include <bsd.own.mk>

REL_NO_KERNEL?=	No
.if ${REL_NO_KERNEL:L} != "yes"
REL_NO_GENERIC?=No
REL_NO_RAMDISK?=No
REL_NO_FLOPPY?=	No
REL_NO_AUTOISO?=No
.else
REL_NO_GENERIC=	Yes
REL_NO_RAMDISK=	Yes
REL_NO_FLOPPY=	Yes
REL_NO_AUTOISO=	Yes
.endif

.if ${REL_NO_GENERIC:L} == "yes"
REL_NO_RAMDISK=	Yes
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
SUBDIR+=	ramdisk
.endif

.if ${_DESCEND} == "yes" || ${REL_NO_FLOPPY:L} != "yes"
SUBDIR+=	floppy
.endif

.if ${_DESCEND} == "yes" || ${REL_NO_AUTOISO:L} != "yes"
SUBDIR+=	iso
.endif

SUBDIR+=	livecd	# only for 'obj', 'clean'

cleannobsd: _SUBDIRUSE

unconfig:
	-cd ramdisk && ${MAKE} unconfig

.include <bsd.subdir.mk>
