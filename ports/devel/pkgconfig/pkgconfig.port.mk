# $MirOS$
#
# module file for ports that use pkgconfig

BUILD_DEPENDS+=		:pkgconfig-*:devel/pkgconfig
PKG_CONFIG_PATH?=	${LOCALBASE}/lib/pkgconfig:${X11BASE}/lib/pkgconfig
CONFIGURE_ENV+=		PKG_CONFIG_PATH=${PKG_CONFIG_PATH:Q}
