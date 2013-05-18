# $MirOS: ports/graphics/png/png.port.mk,v 1.1 2006/02/09 11:11:51 tg Exp $

LIB_DEPENDS+=		png::graphics/png
CPPFLAGS+=		-I${LOCALBASE}/libpng
