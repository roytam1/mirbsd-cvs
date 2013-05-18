# $OpenBSD: Makefile,v 1.5 2002/09/08 12:15:04 avsm Exp $

COMMENT=			convert various Microsoft formats into HTML/PNG

DISTNAME=	wv-0.7.2
CATEGORIES=	converters
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=wvware/}

HOMEPAGE=	http://www.wvware.com/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=	converters/libiconv
LIB_DEPENDS=	wmf.6,wmflite.6::graphics/libwmf \
		png.2::graphics/png \
		Magick.5::graphics/ImageMagick \
		glib.1::devel/glib1

USE_GMAKE= 	Yes
USE_CXX=	Yes
CONFIGURE_STYLE= gnu dest
CONFIGURE_ARGS+= ${CONFIGURE_SHARED} --enable-static
CONFIGURE_ARGS+= --with-png=${LOCALBASE} --with-exporter \
		--with-libiconv=${ICONV_PREFIX} \
		--with-Magick=${LOCALBASE} --with-libwmf=${LOCALBASE}

NO_REGRESS=	Yes

.include <bsd.port.mk>
