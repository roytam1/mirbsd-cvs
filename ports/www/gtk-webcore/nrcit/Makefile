# $MirOS$

COMMENT=		"Gtk-Webcore: embeddable web component"
DISTNAME=		osb-nrcit-${VERSION}

LIB_DEPENDS+=		glib-2.0.400.0::devel/glib
LIB_DEPENDS+=		gdk-x11-2.0.400.0,gtk-x11-2.0.400.0,gdk_pixbuf-2.0.400.0::x11/gtk+
LIB_DEPENDS+=		curl.3::net/curl
LIB_DEPENDS+=		jscore::www/gtk-webcore/jscore
LIB_DEPENDS+=		nrcore,nrcore_kwiq_gtk::www/gtk-webcore/nrcore

PKG_CONFIG_PATH=	${LOCALBASE}/lib/pkgconfig:${X11BASE}/lib/pkgconfig
CONFIGURE_ENV+=		PKG_CONFIG_PATH=${PKG_CONFIG_PATH}

.include <bsd.port.mk>
