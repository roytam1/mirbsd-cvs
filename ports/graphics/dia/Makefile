# $MirOS: ports/graphics/dia/Makefile,v 1.4 2006/06/03 16:02:40 bsiegert Exp $
# $OpenBSD: Makefile,v 1.24 2004/04/02 19:07:04 sturm Exp $

COMMENT=			technical diagrams drawing tool

DISTNAME=	dia-0.92.2
PKGNAME=	${DISTNAME}-1
CATEGORIES=	graphics

HOMEPAGE=	http://www.lysator.liu.se/~alla/dia/

MASTER_SITES=	${MASTER_SITE_GNOME:=sources/dia/0.92/}


# GPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

LIB_DEPENDS=	gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+ \
		art_lgpl_2.5::graphics/libart \
		popt::devel/popt \
		xslt.1::textproc/libxslt \
		xml2.2.6::textproc/libxml \
		unicode.0::devel/libunicode
MODULES+=		devel/pkgconfig graphics/png

USE_GMAKE=		Yes
USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--disable-static --disable-gnome

.include <bsd.port.mk>
