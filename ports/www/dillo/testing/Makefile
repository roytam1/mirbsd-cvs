# $MirOS$
# $OpenBSD: Makefile,v 1.18 2004/02/26 13:43:26 couderc Exp $

COMMENT=		"Fast and light gtk-based web browser (alpha ssl support)"

VERSION=		0.8.3
DASH_VER=		-ssl
DISTNAME=		dillo-${VERSION}
PKGNAME=		${DISTNAME}${DASH_VER}
CATEGORIES=     	www

HOMEPAGE=		http://www.dillo.org/

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# GPL license
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}download/

EXTRACT_SUFX=	.tar.bz2

LIB_DEPENDS=    jpeg.62::graphics/jpeg \
                png.2::graphics/png \
		gtk.1.2,gdk.1.2::x11/gtk+1

USE_GMAKE=		Yes
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS=		--enable-cookies --enable-ipv6
CONFIGURE_ENV=		CPPFLAGS="-I${LOCALBASE}/include -I${LOCALBASE}/include/libpng" \
			LDFLAGS="-L${LOCALBASE}/lib"

.include <bsd.port.mk>
