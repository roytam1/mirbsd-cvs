# $MirOS: ports/x11/gnome/librsvg/Makefile,v 1.9 2007/07/10 19:18:49 bsiegert Exp $
# $OpenBSD: Makefile,v 1.12 2004/12/23 05:03:09 marcm Exp $

COMMENT=		SAX-based render library for SVG files

VERSION=		2.16.1
DASH_VER=		1
DISTNAME=		librsvg-${VERSION}
CATEGORIES=		devel x11/gnome

HOMEPAGE=		http://www.gnome.org

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/librsvg/2.16/}
EXTRACT_SUFX=           .tar.bz2

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=		art_lgpl_2.5::graphics/libart \
			bz2::archivers/bzip2 \
			gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0:gtk+2->=2.10.6-1:x11/gtk+ \
			gnomevfs-2.800.3::x11/gnome/vfs2 \
			gnomecanvas-2.800.0::x11/gnome/libgnomecanvas \
			gnomeprint-2-2::x11/gnome/libgnomeprint \
			gnomeprintui-2-2::x11/gnome/libgnomeprintui \
			gsf-1::devel/libgsf \
			pangoft2-1.0.0.0::devel/pango \
			popt.0.3::devel/popt \
			croco-0.6.3.0:libcroco->=0.6.1:textproc/libcroco \
			xml2.2.6::textproc/libxml
MODULES+=		devel/pkgconfig

USE_X11=		Yes
USE_CXX=		Yes # fam, shared-mime-info, libgsf
USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autogen
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+= 	--disable-gtk-doc
CONFIGURE_ARGS+= 	--with-svgz
CONFIGURE_ARGS+= 	--with-croco

.include <bsd.port.mk>
