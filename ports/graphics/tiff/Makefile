# $MirOS: ports/graphics/tiff/Makefile,v 1.10 2006/02/09 09:35:57 tg Exp $
# $OpenBSD: Makefile,v 1.29 2004/05/18 23:35:35 brad Exp $

COMMENT=			library routines for working with TIFF images
COMMENT-cxx=			library routines for working with TIFF images, C++ API
DESCR=			${PKGDIR}/DESCR
V=			3.7.4
_V=			${V:R:S/.//}.${V:E}
DASH_VER=		-0
DISTNAME=		tiff-${V}
PKGNAME=		${DISTNAME}${DASH_VER}
PKGNAME-cxx=		tiff-cxx-${V}${DASH_VER}
CATEGORIES=		graphics
MASTER_SITES=		ftp://ftp.remotesensing.org/pub/libtiff/
HOMEPAGE=		http://www.remotesensing.org/libtiff/
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

LIB_DEPENDS=    	jpeg.62::graphics/jpeg

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

PSEUDO_FLAVORS=		no_cxx
FLAVOR?=

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
SUBST_VARS+=		V _V

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

.if defined(PACKAGING) && defined(SUBPACKAGE) && !empty(SUBPACKAGE)
LIB_DEPENDS=		tiff::graphics/tiff
.endif

pre-patch:
	rm -f ${WRKSRC}/m4/libtool.m4

post-install:
	cd ${PREFIX}/man/man3; for a in *tiff; do \
		mv $$a $${a%tiff}; \
	done

.include <bsd.port.mk>
