# $MirOS$

.ifndef _MIRPORTS_DEVEL_AUTOCONF_MAKEFILE_INC
_MIRPORTS_DEVEL_AUTOCONF_MAKEFILE_INC=1

.include <mirports.sys.mk>

.if ${OStype} == "MirBSD"
.  if ${OSver:R} < 10
_HAVE_NEW_M4=		No
.  elif ${OSver:R} == 10
.    if ${OSver:E} < 170
_HAVE_NEW_M4=		No
.    else
_HAVE_NEW_M4=		Yes
.    endif
.  else
_HAVE_NEW_M4=		Yes
.  endif
.elif ${OStype} == "MidnightBSD"
_HAVE_NEW_M4=		No
.elif ${OStype} == "OpenBSD"
.  if ${OSrev} < 45
_HAVE_NEW_M4=		No
.  else
_HAVE_NEW_M4=		Yes
.  endif
.elif ${OStype} == "Interix"
_HAVE_NEW_M4=		No
.elif ${OStype} == "Darwin"
_HAVE_NEW_M4=		Yes
.else
.  error Unknown OStype '${OStype}'!
.endif

_NEED_NEW_M4?=		No

.if (${_NEED_NEW_M4:L} == "yes") && (${_HAVE_NEW_M4:L} != "yes")
BUILD_DEPENDS+=		:m4-*:lang/m4
M4=			${LOCALBASE}/bin/gm4
.endif

.endif
