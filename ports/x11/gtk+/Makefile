# $MirOS: ports/x11/gtk+/Makefile,v 1.7 2005/10/09 15:27:06 bsiegert Exp $
# $OpenBSD: Makefile,v 1.14 2004/03/30 15:48:29 sturm Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}
COMMENT=			"multi-platform graphical toolkit"
COMMENT-docs=           	"gtk+-2 documentation"
VERSION=			2.8.6
DISTNAME=			gtk+-${VERSION}
DASH_VER=			-0
PKGNAME=			gtk+2-${VERSION}${DASH_VER}
PKGNAME-docs=			gtk+2-docs-${VERSION}${DASH_VER}
CATEGORIES=			x11 devel
HOMEPAGE=			http://www.gtk.org
RESPONSIBLE=			Benny Siegert <bsiegert@gmx.de>

# LGPL
PERMIT_PACKAGE_CDROM=		Yes
PERMIT_PACKAGE_FTP=		Yes
PERMIT_DISTFILES_CDROM=		Yes
PERMIT_DISTFILES_FTP=		Yes

MASTER_SITES=			ftp://ftp.gtk.org/pub/gtk/v2.8/
EXTRACT_SUFX=           	.tar.bz2

MULTI_PACKAGES=         	-docs
SUBPACKAGE?=

.if ${SUBPACKAGE} != "-docs"
MODULES=			devel/gettext devel/pkgconfig graphics/png

LIB_DEPENDS=			glib-2.0.0.800,gmodule-2.0.0.800,gobject-2.0.0.800::devel/glib \
				pango-1.0.0.1000,pangoft2-1.0.0.1000,pangox-1.0.0.1000,pangoxft-1.0.0.1000::devel/pango \
				atk-1.0.0.1011::devel/atk \
				tiff::graphics/tiff \
				jpeg.62::graphics/jpeg
.endif

.if defined(PACKAGING) && ${SUBPACKAGE} == "-docs"
PKG_ARCH=			*
.endif

USE_X11=			Yes
USE_GMAKE=			Yes
CONFIGURE_STYLE=		autoconf
AUTOCONF_NEW=			Yes

CONFIGURE_ARGS+=		--enable-static
CONFIGURE_ARGS+=		${CONFIGURE_SHARED}
CONFIGURE_ARGS+= 		--disable-gtk-doc

.include <bsd.port.mk>
