# $MirOS$
# $OpenBSD: Makefile,v 1.17 2013/07/09 20:32:52 espie Exp $

COMMENT=		open-source JPEG 2000 codec library
DISTNAME=		openjpeg-2.0.0
CATEGORIES=		graphics
HOMEPAGE=		http://www.openjpeg.org/

# BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		http://openjpeg.googlecode.com/files/
LIB_DEPENDS+=		lcms2::graphics/lcms2
LIB_DEPENDS+=		tiff::graphics/tiff
MODULES+=		graphics/png
MODULES+=		devel/cmake

post-extract:
	cd ${WRKSRC}/src/lib/openmj2 && ln -sf ../openjp2/opj_malloc.h

post-install:
	cd ${PREFIX}/share/doc/ && mv openjpeg-* openjpeg

.include <bsd.port.mk>
