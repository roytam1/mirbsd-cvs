# $MirOS: ports/audio/audacious/player/Makefile,v 1.2 2007/01/07 16:20:12 bsiegert Exp $

# Port contributed by Jonathan Schleifer <js@h3c.de>

COMMENT=		advanced BMP fork
DISTNAME=		audacious-1.2.2
DASH_VER=		1
CATEGORIES=		audio x11

LIB_DEPENDS=		gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+ \
			glade-2.0.0.0::devel/libglade

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-ipv6
CONFIGURE_ARGS+=	--disable-dependency-tracking
CONFIGURE_ARGS+=	--disable-nls
CONFIGURE_ARGS+=	--with-rc-path=.etc/audacious

# build_stamp.c is missing from the 1.2.2 tarball, this is a bug
post-patch:
	print '#!/bin/sh\necho -n MirPorts-${DASH_VER}' \
	    >${WRKDIR}/bin/svnversion
	chmod +x ${WRKDIR}/bin/svnversion

.include <bsd.port.mk>
