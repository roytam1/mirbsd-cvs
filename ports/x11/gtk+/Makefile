# $MirOS: ports/x11/gtk+/Makefile,v 1.17 2009/08/15 20:45:20 bsiegert Exp $
# $OpenBSD: Makefile,v 1.14 2004/03/30 15:48:29 sturm Exp $

NOT_FOR_PLATFORM=		${NOPIC_PLATFORMS}
COMMENT=			multi-platform graphical toolkit
COMMENT-docs=			gtk+-2 documentation
VERSION=			2.12.12
DASH_VER=			0
DISTNAME=			gtk+-${VERSION}
PKGNAME=			gtk+2-${VERSION}-${DASH_VER}
PKGNAME-docs=			gtk+2-docs-${VERSION}-${DASH_VER}
FULLPKGNAME-docs=		${PKGNAME-docs}
CATEGORIES=			x11 devel
HOMEPAGE=			http://www.gtk.org
RESPONSIBLE=			Benny Siegert <bsiegert@gmx.de>

# LGPL
PERMIT_PACKAGE_CDROM=		Yes
PERMIT_PACKAGE_FTP=		Yes
PERMIT_DISTFILES_CDROM=		Yes
PERMIT_DISTFILES_FTP=		Yes

MASTER_SITES+=			${MASTER_SITE_GNOME:=sources/gtk+/${VERSION:R}/}
MASTER_SITES+=			ftp://ftp.gtk.org/pub/gtk/${VERSION:R}/
EXTRACT_SUFX=           	.tar.bz2

MULTI_PACKAGES=         	-docs
SUBPACKAGE?=

FLAVOURS=			cups
FLAVOUR?=

.if ${SUBPACKAGE} != "-docs"
MODULES=			devel/gettext devel/pkgconfig graphics/png x11/gtk+

LIB_DEPENDS=			glib-2.0.0.0,gmodule-2.0.0.0,gobject-2.0.0.0,gthread-2.0.0.0:glib2->=2.16:devel/glib \
				pango-1.0.0.0,pangoft2-1.0.0.0,pangox-1.0.0.0,pangocairo-1.0.0.0:pango->=1.18:devel/pango \
				atk-1.0.0.0::devel/atk \
				tiff::graphics/tiff \
				jpeg::graphics/jpeg
. if ${FLAVOUR:L:Mcups}
LIB_DEPENDS+=			cups,cupsimage::print/cups
. endif
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

.if !${FLAVOUR:L:Mcups}
CONFIGURE_ARGS+=		--disable-cups
.endif

.include <bsd.port.mk>
