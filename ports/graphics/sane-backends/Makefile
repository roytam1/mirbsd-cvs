# $MirOS: ports/graphics/sane-backends/Makefile,v 1.2 2006/02/09 11:11:52 tg Exp $
# Original from: Antoine Jacoutot <ajacoutot@lphp.org>

COMMENT=			API for accessing scanners, backends

DISTNAME=	sane-backends-1.0.14
CATEGORIES=	graphics
MASTER_SITES=	ftp://ftp.sane-project.org/pub/sane/${DISTNAME}/ \
		http://gd.tuwien.ac.at/hci/sane/${DISTNAME}/ \
		ftp://gd.tuwien.ac.at/hci/sane/${DISTNAME}/

HOMEPAGE=	http://www.sane-project.org/

# GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=	devel/gettext
LIB_DEPENDS=	usb.7::devel/libusb \
		jpeg.62::graphics/jpeg

USE_GMAKE=		Yes
AUTOCONF_NEW=		Yes
CONFIGURE_STYLE=	autoconf

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static

FLAVORS=	gphoto2
FLAVOR?=

.if ${FLAVOR:L} == "gphoto2"
LIB_DEPENDS+=		gphoto2::graphics/gphoto2
CONFIGURE_ARGS+=	--with-gphoto2
PLIST=			${PKGDIR}/PLIST.${FLAVOR}
.else
CONFIGURE_ARGS+=	--without-gphoto2
.endif

.include <bsd.port.mk>
