# $MirOS: ports/graphics/tiff/Makefile,v 1.2 2005/04/24 00:09:10 bsiegert Exp $
# $OpenBSD: Makefile,v 1.29 2004/05/18 23:35:35 brad Exp $

COMMENT=		"library routines for working with TIFF images"
COMMENT-cxx=		"library routines for working with TIFF images, C++ API"
DESCR=			${PKGDIR}/DESCR
VERSION=		3.7.2
DASH_VER=	
DISTNAME=		tiff-${VERSION}
PKGNAME=		${DISTNAME}${DASH_VER}
PKGNAME-cxx=		tiff-cxx-${VERSION}${DASH_VER}
CATEGORIES=		graphics
MASTER_SITES=		ftp://ftp.remotesensing.org/pub/libtiff/
HOMEPAGE=		http://www.libtiff.org/
LIB_DEPENDS=    	jpeg.62::graphics/jpeg

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

PSEUDO_FLAVORS=		no_cxx
FLAVOR?=

CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
SEPARATE_BUILD=		concurrent
SUBST_VARS+=		VERSION

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--with-jpeg-include-dir=${LOCALBASE}/include
CONFIGURE_ARGS+=	--with-jpeg-lib-dir=${LOCALBASE}/lib

.if ${FLAVOR:L:Mno_cxx}
CONFIGURE_ARGS+=	--enable-cxx=no
.else
CONFIGURE_ARGS+=	--enable-cxx
USE_CXX=		Yes
MULTI_PACKAGES=		-cxx
.endif

. if defined(PACKAGING) && defined(SUBPACKAGE) && !empty(SUBPACKAGE)
LIB_DEPENDS=		tiff::graphics/tiff
. endif

#NO_REGRESS=	Yes

.include <bsd.port.mk>
