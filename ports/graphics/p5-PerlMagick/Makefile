# $OpenBSD: Makefile,v 1.3 2004/04/13 00:50:45 brad Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=	"object-oriented Perl interface to ImageMagick"

VERSION=	5.2.9
DISTNAME=	ImageMagick-${VERSION}
PKGNAME=	p5-PerlMagick-${VERSION}p1
CATEGORIES=	graphics devel
MASTER_SITES=	${MASTER_SITE_BACKUP}

HOMEPAGE=	http://www.simplesystems.org/ImageMagick/

BUILD_DEPENDS=	:ImageMagick-${VERSION}:graphics/ImageMagick
RUN_DEPENDS=	:ImageMagick-${VERSION}:graphics/ImageMagick
LIB_DEPENDS=	Magick.5::graphics/ImageMagick

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= perl

USE_CXX=	Yes

WRKSRC=	${WRKDIST}/PerlMagick

.include <bsd.port.mk>
