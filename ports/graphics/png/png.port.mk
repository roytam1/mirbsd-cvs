# $MirOS: ports/graphics/png/png.port.mk,v 1.2 2006/03/06 21:58:36 bsiegert Exp $

LIB_DEPENDS+=		png::graphics/png
CPPFLAGS+=		-I${LOCALBASE}/include/libpng
