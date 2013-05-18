# $MirOS: ports/graphics/p5-PerlMagick/Makefile,v 1.4 2005/07/07 21:21:58 bsiegert Exp $
# $OpenBSD: Makefile,v 1.10 2005/06/28 18:08:23 naddy Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			object-oriented Perl interface to ImageMagick

VER=		6.2.3
DASHVER=	3
DISTNAME=	ImageMagick-${VER}-${DASHVER}
PKGNAME=	p5-PerlMagick-${VER}.${DASHVER}-0
CATEGORIES=	graphics devel
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=imagemagick/}

HOMEPAGE=	http://www.imagemagick.org

BUILD_DEPENDS=	:ImageMagick-${VER}.${DASHVER}:graphics/ImageMagick
RUN_DEPENDS=	:ImageMagick-${VER}.${DASHVER}:graphics/ImageMagick
LIB_DEPENDS=	Magick.8::graphics/ImageMagick

# http://www.imagemagick.org/www/Copyright.html
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= perl
USE_CXX=	Yes
WRKDIST=	${WRKDIR}/${DISTNAME:S/-${DASHVER}$//}
WRKSRC=		${WRKDIST}/PerlMagick

post-patch:
	@perl -pi -e 's|%%LOCALBASE%%|${LOCALBASE}|g; \
		s|%%X11BASE%%|${X11BASE}|g;' ${WRKSRC}/Makefile.PL

pre-regress:
	@perl -pi -e 's|\@abs_top_srcdir\@|${WRKDIST}|g; \
		s|\@abs_top_builddir\@|${WRKDIST}|g; \
		s|\@MAGICK_CODER_MODULE_PATH\@|${WRKDIST}/coder|g; \
		s|\@MAGICK_CONFIGURE_SRC_PATH\@|${WRKDIST}/config|g; \
		s|\@MAGICK_CONFIGURE_BUILD_PATH\@|${WRKDIST}/config|g; \
		s|\@MAGICK_FILTER_MODULE_PATH\@|${WRKDIST}/filters|g;'\
		 < ${WRKDIST}/magick.sh.in > ${WRKDIST}/magick.sh

.include <bsd.port.mk>
