# $MirOS: ports/devel/pkgconfig/pkgconfig.port.mk,v 1.1 2005/12/28 00:40:19 bsiegert Exp $
#
# module file for ports that use pkgconfig

BUILD_DEPENDS+=		:pkgconfig-*:devel/pkgconfig
PKG_CONFIG_PATH?=	${LOCALBASE}/lib/pkgconfig:${X11BASE}/lib/pkgconfig:/usr/share/pkgconfig
CONFIGURE_ENV+=		PKG_CONFIG_PATH=${PKG_CONFIG_PATH:Q}
