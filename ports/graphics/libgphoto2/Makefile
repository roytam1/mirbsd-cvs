# $MirOS: ports/graphics/libgphoto2/Makefile,v 1.8 2007/04/07 14:38:37 bsiegert Exp $
# $OpenBSD: Makefile,v 1.4 2004/04/14 18:39:57 brad Exp $

COMMENT=		digital camera library
CATEGORIES=		graphics devel
VERSION=		2.1.6
DISTNAME=		libgphoto2-${VERSION}
PKGNAME=		libgphoto-${VERSION}-${DASH_VER}
HOMEPAGE=		http://gphoto.sourceforge.net/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=gphoto/}

# GPL
PERMIT_PACKAGE_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
MODGNU_RECURSE_DIRS=	${WRKSRC}/libgphoto2_port ${WRKSRC}
CONFIGURE_ARGS+=	--disable-nls

USE_CXX=		Yes # depends on libusb, which uses C++
SUBST_VARS+=		VERSION
MODULES+=		devel/pkgconfig
LIB_DEPENDS+=		exif:libexif->=0.6.13-1:graphics/libexif \
			jpeg::graphics/jpeg \
			usb::devel/libusb

.include <bsd.port.mk>
