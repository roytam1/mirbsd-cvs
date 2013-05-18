# $MirOS: ports/devel/pkgconfig/pkgconfig.port.mk,v 1.5 2008/12/26 15:42:05 tg Exp $
#
# module file for ports that use pkgconfig

BUILD_DEPENDS+=		:pkgconfig->=0.23:devel/pkgconfig
PKG_CONFIG_PATH?=	/usr/libdata/pkgconfig:${LOCALBASE}/libdata/pkgconfig:${LOCALBASE}/lib/pkgconfig:${X11BASE}/lib/pkgconfig
CONFIGURE_ENV+=		PKG_CONFIG_PATH=${PKG_CONFIG_PATH:Q}
MAKE_ENV+=		PKG_CONFIG_PATH=${PKG_CONFIG_PATH:Q}
