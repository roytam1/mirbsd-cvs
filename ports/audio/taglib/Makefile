# $MirOS: ports/x11/libxklavier/Makefile,v 1.2 2006/02/09 11:15:51 tg Exp $

COMMENT=		audio metadata library

VERSION=		1.4
DISTNAME=		taglib-${VERSION}
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
CONFIGURE_ARGS+=	--disable-dependency-tracking

.include <bsd.port.mk>
