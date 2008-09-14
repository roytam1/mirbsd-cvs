# $MirOS: ports/aqua/qt4-mac/Makefile,v 1.1 2008/07/02 18:49:41 bsiegert Exp $

COMMENT=		Qt toolkit, Aqua version for Mac OS
COMMENT-docs=		Qt documentation, Aqua version for Mac OS
COMMENT-examples=	Qt examples, Aqua version for Mac OS

ONLY_FOR_PLATFORM=	Darwin:*:*

VERSION=		4.4.1
DISTNAME=		qt-mac-opensource-src-${VERSION}
PKGNAME=		qt-mac-${VERSION}-${DASH_VER}
PKGNAME-docs=		qt-mac-docs-${VERSION}-${DASH_VER}
PKGNAME-examples=	qt-mac-examples-${VERSION}-${DASH_VER}
CATEGORIES=		aqua devel
EXTRACT_SUFX=		.tar.bz2

HOMEPAGE=		http://trolltech.com/products/qt/homepage
MASTER_SITES=		http://ftp.trolltech.com/qt/source/

# QPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MULTI_PACKAGES=		-docs -examples
SUBPACKAGE?=

MODULES+=		graphics/png

USE_X11=		Yes
USE_CXX=		Yes
#USE_GMAKE=		Yes
CONFIGURE_STYLE= 	simple

CONFIGURE_ARGS+=	-prefix ${PREFIX}/qt4
CONFIGURE_ARGS+=	-stl
CONFIGURE_ARGS+=	-no-phonon -no-webkit
CONFIGURE_ARGS+=	-confirm-license
CONFIGURE_ARGS+=	-v # -fast
CONFIGURE_ARGS+=	-I${PREFIX}/include -L${PREFIX}/lib

EXTRA_FAKE_FLAGS=	INSTALL_ROOT=${DESTDIR:Q}

.if defined(PACKAGING) && ${SUBPACKAGE} == "-examples"
LIB_DEPENDS+=		../qt4/lib/QtCore.la:qt-mac->=4.0:aqua/qt4-mac
.endif

post-install:
	find ${PREFIX:Q} -name "*.la" -exec perl -pi -e "s/^old_library='.*'/old_library=''/" \{\} \;

.include <bsd.port.mk>
