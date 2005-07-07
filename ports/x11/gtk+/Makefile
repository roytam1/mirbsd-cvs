# $MirOS: ports/x11/gtk+/Makefile,v 1.2 2005/04/02 20:32:53 bsiegert Exp $
# $OpenBSD: Makefile,v 1.14 2004/03/30 15:48:29 sturm Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}
COMMENT=			"multi-platform graphical toolkit"
COMMENT-docs=           	"gtk+-2 documentation"
VERSION=			2.4.14
DISTNAME=			gtk+-${VERSION}
PKGNAME=			gtk+2-${VERSION}-0
PKGNAME-docs=			gtk+2-docs-${VERSION}-0
CATEGORIES=			x11 devel
HOMEPAGE=			http://www.gtk.org
RESPONSIBLE=			Benny Siegert <bsiegert@gmx.de>

# LGPL
PERMIT_PACKAGE_CDROM=		Yes
PERMIT_PACKAGE_FTP=		Yes
PERMIT_DISTFILES_CDROM=		Yes
PERMIT_DISTFILES_FTP=		Yes

MASTER_SITES=			ftp://ftp.gtk.org/pub/gtk/v2.4/
EXTRACT_SUFX=           	.tar.bz2

MULTI_PACKAGES=         	-docs
SUBPACKAGE?=

.if ${SUBPACKAGE} != "-docs"
MODULES=			devel/gettext

LIB_DEPENDS=			glib-2.0.400.0,gmodule-2.0.400.0,gobject-2.0.400.0::devel/glib \
				pango-1.0.399.1,pangoft2-1.0.399.1,pangox-1.0.399.1,pangoxft-1.0.399.1::devel/pango \
				atk-1.0.0.1::devel/atk \
				tiff.35::graphics/tiff \
				png.3::graphics/png \
				jpeg.62::graphics/jpeg
BUILD_DEPENDS=          	:pkgconfig-*:devel/pkgconfig
.endif

.if defined(PACKAGING) && ${SUBPACKAGE} == "-docs"
PKG_ARCH=			*
.endif

USE_X11=			Yes
USE_GMAKE=			Yes
CPPFLAGS+=			-I${X11BASE}/include/freetype2/ -I${LOCALBASE}/include/libpng
CONFIGURE_STYLE=		autoconf
AUTOCONF_NEW=			Yes
CONFIGURE_ARGS+= 		--disable-gtk-doc
MAKE_ENV=			PKG_CONFIG_PATH="${LOCALBASE}/lib/pkgconfig:${X11BASE}/lib/pkgconfig"
CONFIGURE_ENV+=			${MAKE_ENV}
NO_SYSTRACE=			"normalize_filename: filename too long"

.include <bsd.port.mk>
