# $MirOS: ports/multimedia/libdv/Makefile,v 1.3 2005/03/30 18:13:37 bsiegert Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/06/26 18:00:27 sturm Exp $

COMMENT=		"Quasar DV codec"

DISTNAME=		libdv-0.102
CATEGORIES=		multimedia

HOMEPAGE=		http://libdv.sourceforge.net/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=libdv/}

LIB_DEPENDS=		SDL.2::devel/sdl \
			gdk.1.2,gtk.1.2::x11/gtk+1 \
			glib.1.2,gmodule.1.2::devel/glib1 \
			popt.0::devel/popt
MODULES+=		devel/pkgconfig

USE_X11=		Yes
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--with-gnu-ld=no --enable-sdl --enable-gtk \
			--with-x --without-debug

.include <bsd.port.mk>
