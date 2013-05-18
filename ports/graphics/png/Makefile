# $MirOS: ports/graphics/png/Makefile,v 1.10 2008/10/22 19:14:49 tg Exp $
# $OpenBSD: Makefile,v 1.46 2004/07/06 22:17:48 brad Exp $

COMMENT=		library for manipulating PNG images
DISTNAME=		libpng-1.2.32
DASH_VER=		1
PKGNAME=		${DISTNAME:S/lib//}-${DASH_VER}
CATEGORIES=		graphics
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=libpng/}
HOMEPAGE=		http://www.libpng.org/pub/png/libpng.html

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

BUILD_DEPENDS+=		:mirmake->=20081012:devel/mirmake
BUILD_DEPENDS+=		::devel/libtool

FAKE_FLAGS=		DESTDIR=${WRKINST:Q} PREFIX=${PREFIX:Q}
MAKE_FILE=		scripts/makefile.openbsd
EXTRA_XAKE_FLAGS+=	LTMIRMAKE=Yes
REGRESS_TARGET=		test

.include <bsd.port.mk>
