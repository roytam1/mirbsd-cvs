# $MirOS: ports/devel/pkgconfig/pkgconfig.port.mk,v 1.3 2007/05/08 22:43:41 tg Exp $
#
# module file for ports that use pkgconfig

BUILD_DEPENDS+=		:pkgconfig->=0.15.0-2:devel/pkgconfig
PKG_CONFIG_PATH?=	${LOCALBASE}/lib/pkgconfig:${X11BASE}/lib/pkgconfig:/usr/libdata/pkgconfig
CONFIGURE_ENV+=		PKG_CONFIG_PATH=${PKG_CONFIG_PATH:Q}
