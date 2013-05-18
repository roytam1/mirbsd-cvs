# $MirOS$

LIB_DEPENDS+=			ncursesw::devel/libncursesw
CPPFLAGS+=			-I${LOCALBASE}/include/ncursesw
CPPFLAGS+=			-D_XOPEN_SOURCE_EXTENDED
