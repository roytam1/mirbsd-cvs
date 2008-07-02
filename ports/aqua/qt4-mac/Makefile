# $MirOS: ports/x11/libxklavier/Makefile,v 1.4 2007/07/03 19:54:42 bsiegert Exp $

COMMENT=		Qt toolkit, Aqua version for Mac OS

ONLY_FOR_PLATFORM=	Darwin:*:*

VERSION=		4.3.3
DISTNAME=		qt-mac-opensource-src-${VERSION}
PKGNAME=		qt-mac-${VERSION}-${DASH_VER}
CATEGORIES=		aqua devel

HOMEPAGE=		http://trolltech.com/products/qt/homepage
MASTER_SITES=		ftp://ftp.trolltech.com/qt/source/

# QPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES+=		graphics/png

USE_X11=		Yes
USE_CXX=		Yes
#USE_GMAKE=		Yes
CONFIGURE_STYLE= 	simple

CONFIGURE_ARGS+=	-prefix ${PREFIX}/qt4
CONFIGURE_ARGS+=	-stl
CONFIGURE_ARGS+=	-confirm-license
CONFIGURE_ARGS+=	-v -fast
CONFIGURE_ARGS+=	-I${PREFIX}/include -L${PREFIX}/lib

EXTRA_FAKE_FLAGS=	INSTALL_ROOT=${DESTDIR:Q}

post-install:
	find ${PREFIX:Q} -name "*.la" -exec perl -pi -e "s/^old_library='.*'/old_library=''/" \{\} \;

.include <bsd.port.mk>
