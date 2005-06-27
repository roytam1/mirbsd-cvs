# $MirOS: ports/graphics/ImageMagick/Makefile,v 1.2 2005/06/27 10:56:35 tg Exp $
# $OpenBSD: Makefile,v 1.64 2004/03/08 23:36:50 xsa Exp $

BROKEN=		neither gnu nor autoconf styles work; update recommended

COMMENT=	"display and manipulate images under X11"
DISTNAME=	ImageMagick-5.2.9
PKGNAME=	${DISTNAME}p0
CATEGORIES=     graphics
MASTER_SITES=	${MASTER_SITE_BACKUP}
HOMEPAGE=	http://www.simplesystems.org/ImageMagick/

LIB_DEPENDS=	bz2.10::archivers/bzip2 \
		jbig.1.2::graphics/jbigkit \
		mpeg.13::graphics/mpeg-lib \
		png.2::graphics/png \
		tiff.35::graphics/tiff \
		ttf.1.3::print/freetype \
		xml2.6::textproc/libxml
BUILD_DEPENDS=	:transfig-*:print/transfig \
		:netpbm-*:graphics/netpbm
RUN_DEPENDS=	${BUILD_DEPENDS}

# XXX whatever?
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
USE_CXX=		Yes
SEPARATE_BUILD=		concurrent
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--enable-static --enable-lzw --enable-16bit-pixel \
			--without-perl --without-modules --without-dps \
			--without-fpx --without-hdf --without-lcms \
			--without-ttf --without-wmf ${CONFIGURE_SHARED}
CPPFLAGS+=		-I${LOCALBASE}/include/libpng \
			-I${LOCALBASE}/include/freetype1/freetype \
			-I${LOCALBASE}/include/libxml2

.include <bsd.port.mk>
