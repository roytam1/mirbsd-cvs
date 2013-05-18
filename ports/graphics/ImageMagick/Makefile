# $MirOS: ports/graphics/ImageMagick/Makefile,v 1.8 2006/02/09 09:35:52 tg Exp $
# $OpenBSD: Makefile,v 1.83 2005/06/28 18:08:23 naddy Exp $

COMMENT=	"image processing tools"

VER=		6.2.3
DASHVER=	3
DISTNAME=	ImageMagick-${VER}-${DASHVER}
PKGNAME=	ImageMagick-${VER}.${DASHVER}-1
CATEGORIES=	graphics

HOMEPAGE=	http://www.imagemagick.org
MASTER_SITES=	${HOMEPAGE}/download/ \
		${MASTER_SITE_SOURCEFORGE:=imagemagick/}

LIB_DEPENDS+=	bz2.10::archivers/bzip2 \
		jbig.1.2::graphics/jbigkit \
		png::graphics/png \
		tiff::graphics/tiff \
		xml2::textproc/libxml \
		lcms.1::graphics/lcms \
		jasper.1::graphics/jasper \
		ltdl::devel/libtool

RUN_DEPENDS=	::graphics/mpeg-lib
BUILD_DEPENDS=	${RUN_DEPENDS}

REGRESS_DEPENDS= ::graphics/p5-PerlMagick

# http://www.imagemagick.org/www/Copyright.html
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_CXX=	Yes
CONFIGURE_STYLE= autoconf
AUTOCONF_NEW=	Yes
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --with-quantum-depth=16 \
		 --without-dot \
		 --without-dps \
		 --without-fpx \
		 --without-modules \
		 --without-threads \
		 --without-perl \
		 --without-wmf \
		 --disable-ltdl-install

CPPFLAGS+=		-I${LOCALBASE}/include/libxml2
LDFLAGS+=		-L${WRKBUILD}/magick/.libs -L${WRKBUILD}/wand/.libs
CONFIGURE_ENV+=		ac_cv_path_LaunchDelegate=no

FLAVORS=	no_x11
FLAVOR?=

.if ${FLAVOR:L:Mno_x11}
BUILD_DEPENDS+=	:ghostscript-*:print/ghostscript/gnu,no_x11
RUN_DEPENDS+=	:ghostscript-*:print/ghostscript/gnu,no_x11
CONFIGURE_ARGS+= --without-x --without-ttf
CONFIGURE_ENV+=	ac_cv_path_FIGDecodeDelegate=no
.else
BUILD_DEPENDS+=	:ghostscript-*:print/ghostscript/gnu
RUN_DEPENDS+=	:ghostscript-*:print/ghostscript/gnu
USE_X11=	Yes
RUN_DEPENDS+=	:transfig-*:print/transfig
BUILD_DEPENDS+=	:transfig-*:print/transfig
.endif

RUN_DEPENDS+=	:netpbm-*:graphics/netpbm
BUILD_DEPENDS+=	:netpbm-*:graphics/netpbm

WRKDIST=	${WRKDIR}/${DISTNAME:S/-${DASHVER}$//}

post-install:
	@perl -pi -e s#'-L${WRKBUILD}/(magick|wand)/.libs '#''#g \
		${PREFIX}/bin/Magick-config
.for f in Magick++ Magick Wand
	@perl -pi -e s#'-L${WRKBUILD}/(magick|wand)/.libs '#''#g \
		${PREFIX}/lib/lib${f}.la
.endfor

.include <bsd.port.mk>
