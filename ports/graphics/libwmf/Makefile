# $MirOS: ports/graphics/libwmf/Makefile,v 1.4 2007/08/20 19:20:43 bsiegert Exp $
# $OpenBSD: Makefile,v 1.7 2004/02/26 16:40:11 espie Exp $

COMMENT=	WMF handling and conversion library
DISTNAME=	libwmf-0.2.8.4
DASH_VER=	1
CATEGORIES=	graphics devel
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=wvware/}

HOMEPAGE=	http://www.wvware.com/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS+=		xml2::textproc/libxml
LIB_DEPENDS+=		jpeg::graphics/jpeg
LIB_DEPENDS+=		gdk_pixbuf-2.0.0.0::x11/gtk+
MODULES+=		graphics/png

USE_X11=	Yes

CONFIGURE_STYLE= autoconf
AUTOCONF_NEW=	Yes
CONFIGURE_ARGS+= ${CONFIGURE_SHARED} --enable-static
CONFIGURE_ARGS+= --with-png=${LOCALBASE} --with-freetype=${X11BASE}
CONFIGURE_ARGS+= --with-jpeg=${LOCALBASE} --with-zlib=/usr

.include <bsd.port.mk>
