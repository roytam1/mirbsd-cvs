# $MirOS: ports/www/dillo/stable/Makefile,v 1.4 2006/02/09 11:15:32 tg Exp $
# $OpenBSD: Makefile,v 1.18 2004/02/26 13:43:26 couderc Exp $

COMMENT=		"Fast and light gtk-based web browser"

VERSION=		0.8.6
DASH_VER=		-0
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

EXTRACT_SUFX=		.tar.bz2

LIB_DEPENDS+=		jpeg.62::graphics/jpeg \
			gtk.1.2,gdk.1.2::x11/gtk+1
RUN_DEPENDS+=		::net/wget
MODULES+=		graphics/png

USE_GMAKE=		Yes
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--enable-cookies
CONFIGURE_ARGS+=	--disable-dlgui
CONFIGURE_ARGS+=	--disable-threaded-dns
FAKE_ENV+=		sysconfdir="${LOCALBASE}/share/examples/dillo"

.include <bsd.port.mk>
