# $MirOS: ports/graphics/tiff/Makefile,v 1.18 2009/08/16 17:25:50 tg Exp $
# $OpenBSD: Makefile,v 1.29 2004/05/18 23:35:35 brad Exp $

COMMENT=		library routines for working with TIFF images
COMMENT-cxx=		C++ API for working with TIFF images
DESCR=			${PKGDIR}/DESCR
VSN=			3.7.4
_V=			${VSN:R:S/.//}.${VSN:E}
DASH_VER=		1
DISTNAME=		tiff-${VSN}
PKGNAME-cxx=		tiff-cxx-${VSN}-${DASH_VER}
CATEGORIES=		graphics
MASTER_SITES=		http://dl.maptools.org/dl/libtiff/old/
HOMEPAGE=		http://www.remotesensing.org/libtiff/
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

BUILD_DEPENDS+=		:jpeg->=6b-4:graphics/jpeg \
			::graphics/jpeg:patch
LIB_DEPENDS+=		jpeg.62::graphics/jpeg

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

PSEUDO_FLAVOURS=	no_cxx
FLAVOUR?=

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
SUBST_VARS+=		_V

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-old-jpeg
CONFIGURE_ARGS+=	--enable-rpath

.if ${FLAVOUR:L:Mno_cxx}
CONFIGURE_ARGS+=	--enable-cxx=no
.else
CONFIGURE_ARGS+=	--enable-cxx
USE_CXX=		Yes
MULTI_PACKAGES=		-cxx
.endif

.if defined(PACKAGING) && defined(SUBPACKAGE) && !empty(SUBPACKAGE)
LIB_DEPENDS=		tiff::graphics/tiff
.endif

post-patch:
	cp ${WRKDIR}/graphics/jpeg/jpeg-6b/jpegint.h ${WRKSRC}/libtiff/

post-install:
	cd ${PREFIX}/man/man3; for a in *tiff; do \
		mv $$a $${a%tiff}; \
	done

.include <bsd.port.mk>
