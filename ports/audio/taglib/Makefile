# $MirOS: ports/audio/taglib/Makefile,v 1.1 2006/11/24 23:15:51 bsiegert Exp $

COMMENT=		audio metadata library

VERSION=		1.4
DISTNAME=		taglib-${VERSION}
PKGNAME=		${DISTNAME}-1
CATEGORIES=		audio devel

HOMEPAGE=		http://developer.kde.org/~wheeler/taglib.html
MASTER_SITES=		http://developer.kde.org/~wheeler/files/src/

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

#LIB_DEPENDS+=		xml2::textproc/libxml

MODULES=		devel/pkgconfig

USE_CXX=		Yes
CONFIGURE_STYLE= 	autogen
AUTOCONF_NEW=		Yes

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static
CONFIGURE_ARGS+=	--disable-dependency-tracking

pre-patch:
	print "/^# libtool.m4/,$$ d\nwq" | ed -s ${WRKSRC}/acinclude.m4

.include <bsd.port.mk>
