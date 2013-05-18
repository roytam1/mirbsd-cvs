# $MirOS: ports/devel/libncursesw/libncursesw.port.mk,v 1.1 2006/10/27 15:53:09 tg Exp $

.if !exists(/usr/lib/libncursesw.a)
LIB_DEPENDS+=			ncursesw::devel/libncursesw
CPPFLAGS+=			-I${LOCALBASE}/include/ncursesw
.endif
CPPFLAGS+=			-D_XOPEN_SOURCE_EXTENDED
