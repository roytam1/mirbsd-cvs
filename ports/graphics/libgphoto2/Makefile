# $MirOS$
# $OpenBSD: Makefile,v 1.4 2004/04/14 18:39:57 brad Exp $

COMMENT=	'digital camera library'
CATEGORIES=	graphics devel
VERSION=	2.1.4
DISTNAME=	libgphoto2-${VERSION}
PKGNAME=	libgphoto-${VERSION}
HOMEPAGE=	http://gphoto.sourceforge.net/
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=gphoto/}

# GPL
PERMIT_PACKAGE_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/libgphoto2_port
SEPARATE_BUILD=		simple
CONFIGURE_ARGS=		--disable-nls

SUBST_VARS=		VERSION

LIB_DEPENDS=		exif::graphics/libexif \
			jpeg::graphics/jpeg \
			usb::devel/libusb
BUILD_DEPENDS=		::devel/pkgconfig

.include <bsd.port.mk>
