# $MirOS: ports/www/dillo/testing/Makefile,v 1.6 2006/12/20 15:32:02 tg Exp $
# $OpenBSD: Makefile,v 1.18 2004/02/26 13:43:26 couderc Exp $

COMMENT=		Fast and light gtk-based web browser (alpha ssl support)

VERSION=		0.8.3
DISTNAME=		dillo-${VERSION}
PKGNAME=		${DISTNAME}-${DASH_VER}-ssl
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
		gtk.1.2,gdk.1.2::x11/gtk+1
MODULES+=		graphics/png

USE_GMAKE=		Yes
USE_X11=		Yes
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS=		--enable-cookies --enable-ipv6

.include <bsd.port.mk>
