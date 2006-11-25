# $MirOS$

# Port contributed by Jonathan Schleifer <js@h3c.de>

COMMENT=		advanced BMP fork
DISTNAME=		audacious-1.2.2
CATEGORIES=		audio x11

LIB_DEPENDS=		gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+ \
			glade-2.0.0.0::devel/libglade

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-ipv6
CONFIGURE_ARGS+=	--disable-dependency-tracking
CONFIGURE_ARGS+=	--disable-nls
CONFIGURE_ARGS+=	--with-rc-path=.etc/audacious

.include <bsd.port.mk>
