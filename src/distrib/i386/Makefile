# $MirOS: src/distrib/i386/Makefile,v 1.7 2006/07/03 22:08:05 tg Exp $

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
.  if ${_DESCEND} == "yes" || ${REL_NO_GENERIC:L} != "yes"
SUBDIR+=	ramdisk
.  endif
SUBDIR+=	floppy
.endif

SUBDIR+=	livecd	# only for 'obj', 'clean'

cleannobsd: _SUBDIRUSE

unconfig:
	-cd ramdisk && ${MAKE} unconfig

.include <bsd.subdir.mk>
