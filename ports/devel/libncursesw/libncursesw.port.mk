# $MirOS: ports/devel/libncursesw/libncursesw.port.mk,v 1.2 2006/10/30 12:54:16 tg Exp $

# Valid choices: any, base, port
USE_NCURSESW?=			any

.if ${USE_NCURSESW:L:Many}
.  if ${OStype} != "MirBSD"
USE_NCURSESW=			port
.  elif exists(/usr/lib/libncursesw.a)
USE_NCURSESW=			base
.  else
USE_NCURSESW=			port
.  endif
.endif

.if ${USE_NCURSESW:L:Mport}
LIB_DEPENDS+=			ncursesw::devel/libncursesw
CPPFLAGS+=			-I${LOCALBASE}/include/ncursesw
.elif !${USE_NCURSESW:L:Mbase}
.  error USE_NCURSESW=${USE_NCURSESW:L} invalid
.endif
CPPFLAGS+=			-D_XOPEN_SOURCE_EXTENDED
