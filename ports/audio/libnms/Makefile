# $MirOS: ports/audio/taglib/Makefile,v 1.2 2006/11/24 23:41:15 bsiegert Exp $

COMMENT=		open media streaming client library

VERSION=		0.6.0
DISTNAME=		libnms-${VERSION}
CATEGORIES=		audio devel

HOMEPAGE=		http://streaming.polito.it/client/library
MASTER_SITES=		http://streaming.polito.it/files/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

#LIB_DEPENDS+=		xml2::textproc/libxml

MODULES=		devel/pkgconfig

CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static
CONFIGURE_ARGS+=	--disable-dependency-tracking
CONFIGURE_ARGS+=	--enable-ipv6



.include <bsd.port.mk>
