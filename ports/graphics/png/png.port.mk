# $MirOS: ports/graphics/png/png.port.mk,v 1.3 2006/06/25 01:56:00 tg Exp $

.if !exists(/usr/lib/libpng.a)
LIB_DEPENDS+=		png::graphics/png
CPPFLAGS+=		-I${LOCALBASE}/include/libpng
.endif
