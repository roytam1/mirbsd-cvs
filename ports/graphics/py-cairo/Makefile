# $MirOS: ports/devel/py-gobject/Makefile,v 1.1 2007/07/19 16:48:44 bsiegert Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=		cairo Python bindings

VERSION=		1.2.6
DISTNAME=		pycairo-${VERSION}
PKGNAME=		py-cairo-${VERSION}-${DASH_VER}
CATEGORIES=		devel

HOMEPAGE=		http://cairographics.org/pycairo/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://cairographics.org/releases/

MODULES=		devel/gettext devel/pkgconfig
BUILD_DEPENDS+=		::math/py-Numeric
LIB_DEPENDS+=		cairo::graphics/cairo

USE_X11=		Yes
CONFIGURE_STYLE=	autoconf
USE_GMAKE=		Yes
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS=		${CONFIGURE_SHARED} --enable-thread

# we cannot use python.port.mk because we do not use distutils
PYTHON_VERSION=		2.3
SUBST_VARS+=		PYTHON_VERSION

.include <bsd.port.mk>
