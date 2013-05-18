# $MirOS: ports/graphics/gdk-pixbuf/Makefile,v 1.3 2005/07/07 21:21:39 bsiegert Exp $
# $OpenBSD: Makefile,v 1.30 2004/03/02 07:57:21 brad Exp $

COMMENT=	"GdkPixbuf graphics library"
COMMENT-gnome=	"GdkPixbuf graphics library (GNOME Canvas)"
VERSION=	0.22.0
DISTNAME=	gdk-pixbuf-${VERSION}
PKGNAME-gnome=	gdk-pixbuf-gnome-${VERSION}-0
CATEGORIES=	graphics
HOMEPAGE=	http://developer.gnome.org/arch/imaging/gdkpixbuf.html

# GNU GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_GNOME:=sources/gdk-pixbuf/0.22/}

CONFIGURE_STYLE=autoconf
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --disable-modules \
		 --disable-mmx \
		 --disable-gtk-doc \
		 --with-html-dir="${PREFIX}/share/doc"
CONFIGURE_ENV=  CPPFLAGS="-I${LOCALBASE}/include/libpng -I${LOCALBASE}/include" \
		LDFLAGS="-L${LOCALBASE}/lib"

PSEUDO_FLAVORS=	no_gnome
FLAVOR?=

MULTI_PACKAGES=
.if !${FLAVOR:L:Mno_gnome}
MULTI_PACKAGES+= -gnome
USE_CXX=	Yes
BROKEN=		GNOME 1 has been removed
.endif
SUBPACKAGE?=

LIB_DEPENDS+=	jpeg.62::graphics/jpeg \
		png.2::graphics/png \
		tiff.35.::graphics/tiff \
		gtk.1.2,gdk.1.2::x11/gtk+1

.if defined(PACKAGING)
. if ${SUBPACKAGE} == "-gnome"
LIB_DEPENDS+=	gnome.36,art_lgpl,gnomesupport,gnomeui::x11/gnome/libs \
		gdk_pixbuf.2::graphics/gdk-pixbuf
. endif
.else
. if ${MULTI_PACKAGES:M-gnome}
LIB_DEPENDS+=	gnome.36,art_lgpl,gnomesupport,gnomeui::x11/gnome/libs
. endif
.endif

.include <bsd.port.mk>
