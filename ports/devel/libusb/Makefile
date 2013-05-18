# $MirOS: ports/devel/libusb/Makefile,v 1.5 2006/02/07 20:17:30 tg Exp $
# $OpenBSD: Makefile,v 1.11 2004/04/21 03:04:14 naddy Exp $

COMMENT=			USB access library
DISTNAME=		libusb-0.1.10a
CATEGORIES=		devel
HOMEPAGE=		http://libusb.sourceforge.net/

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
