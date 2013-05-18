# $MirOS: ports/devel/pkgconfig/pkgconfig.port.mk,v 1.4 2007/07/05 22:18:11 tg Exp $
#
# module file for ports that use pkgconfig

BUILD_DEPENDS+=		:pkgconfig->=0.15.0-2:devel/pkgconfig
PKG_CONFIG_PATH?=	/usr/libdata/pkgconfig:${LOCALBASE}/libdata/pkgconfig:${LOCALBASE}/lib/pkgconfig:${X11BASE}/lib/pkgconfig
CONFIGURE_ENV+=		PKG_CONFIG_PATH=${PKG_CONFIG_PATH:Q}
