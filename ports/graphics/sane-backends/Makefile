# $MirOS: ports/graphics/sane-backends/Makefile,v 1.6 2008/10/14 19:38:24 tg Exp $
# Original from: Antoine Jacoutot <ajacoutot@lphp.org>

COMMENT=	API for accessing scanners, backends
DISTNAME=	sane-backends-1.0.14
CATEGORIES=	graphics
HOMEPAGE=	http://www.sane-project.org/

# GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.sane-project.org/pub/sane/${DISTNAME}/ \
		http://gd.tuwien.ac.at/hci/sane/${DISTNAME}/ \
		ftp://gd.tuwien.ac.at/hci/sane/${DISTNAME}/ \
		${MASTER_SITE_FINK}

MODULES=	devel/gettext
LIB_DEPENDS=	usb.7::devel/libusb \
		jpeg.62::graphics/jpeg

USE_CXX=		Yes # depends on libusb, which uses C++
USE_GMAKE=		Yes
AUTOCONF_NEW=		Yes
CONFIGURE_STYLE=	autoconf

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static

FLAVOURS=	gphoto2
FLAVOUR?=

.if ${FLAVOUR:L} == "gphoto2"
LIB_DEPENDS+=		gphoto2::graphics/gphoto2
CONFIGURE_ARGS+=	--with-gphoto2
PLIST=			${PKGDIR}/PLIST.${FLAVOUR}
.else
CONFIGURE_ARGS+=	--without-gphoto2
.endif

.include <bsd.port.mk>
