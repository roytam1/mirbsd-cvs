# $MirOS: ports/graphics/libgphoto2/Makefile,v 1.5 2006/09/14 00:09:58 tg Exp $
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
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/libgphoto2_port
CONFIGURE_ARGS+=	--disable-nls \
			--disable-libtool-lock

SUBST_VARS+=		VERSION
MODULES+=		devel/pkgconfig
LIB_DEPENDS+=		exif:libexif->=0.6.13-1:graphics/libexif \
			jpeg::graphics/jpeg \
			usb::devel/libusb

.include <bsd.port.mk>
