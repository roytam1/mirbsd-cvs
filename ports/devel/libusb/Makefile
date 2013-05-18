# $MirOS: ports/devel/libusb/Makefile,v 1.7 2008/08/26 18:46:02 tg Exp $
# $OpenBSD: Makefile,v 1.11 2004/04/21 03:04:14 naddy Exp $

COMMENT=		USB access library
DISTNAME=		libusb-0.1.12
CATEGORIES=		devel
HOMEPAGE=		http://www.libusb.org/

# LGPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=libusb/}

USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--disable-build-docs
CONFIGURE_ENV+=		libusb_cv_path_doxygen=false

.include <bsd.port.mk>
