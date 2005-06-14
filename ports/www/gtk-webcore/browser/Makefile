# $MirOS$

COMMENT=		"Gtk-Webcore: reference browser implementation"
DISTNAME=		osb-browser-${VERSION}

LIB_DEPENDS+=		gdk-x11-2.0.400.0,gtk-x11-2.0.400.0,gdk_pixbuf-2.0.400.0::x11/gtk+
LIB_DEPENDS+=		glade-2.0.0.0::devel/libglade
LIB_DEPENDS+=		nrcit::www/gtk-webcore/nrcit

PKG_CONFIG_PATH=	${LOCALBASE}/lib/pkgconfig:${X11BASE}/lib/pkgconfig
CONFIGURE_ENV+=		PKG_CONFIG_PATH=${PKG_CONFIG_PATH}

.include <bsd.port.mk>
