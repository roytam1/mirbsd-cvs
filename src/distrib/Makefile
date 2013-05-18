# $MirOS: src/distrib/Makefile,v 1.13 2008/07/12 22:06:12 tg Exp $

.include <bsd.own.mk>

REL_NO_GENERIC?=	No
REL_NO_RAMDISK?=	No
.if ${REL_NO_GENERIC:L} != "no"
REL_NO_RAMDISK=		Yes
.endif

.if make(obj) || make(clean) || make(cleandir) || make(cleannobsd)
_DESCEND=		Yes
.else
_DESCEND=		No
.endif

SUBDIR=

.if ${_DESCEND} == "Yes" || (${REL_NO_RAMDISK:L} == "no" && !make(install))
  SUBDIR+=		special
.endif

.if ${_DESCEND} == "Yes" || ${REL_NO_GENERIC:L} == "no"
  SUBDIR+=		generic
.endif

.if ${_DESCEND} == "Yes" || ${REL_NO_RAMDISK:L} == "no"
  SUBDIR+=		common
  SUBDIR+=		common/extra
.  if ${_DESCEND} == "Yes" || ${MACHINE} == "i386"
  SUBDIR+=		common/autosshd
.  endif
.  if ${_DESCEND} == "Yes"
  SUBDIR+=		common/grml
  SUBDIR+=		common/netboot.me
.  endif
.endif

.if ${_DESCEND} == "Yes"
  SUBDIR+=		baselive
  SUBDIR+=		tools
.endif

cleannobsd: _SUBDIRUSE

unconfig:
	-cd common && ${MAKE} unconfig

.include <bsd.subdir.mk>
