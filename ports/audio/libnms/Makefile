# $MirOS: ports/audio/libnms/Makefile,v 1.2 2007/02/22 22:57:43 tg Exp $

COMMENT=		open media streaming client library

VERSION=		0.6.0
DASH_VER=		1
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
CONFIGURE_ARGS+=	--enable-ipv6

pre-build:
.for i in autoconf automake aclocal
	ln -sf /bin/true ${WRKDIR}/bin/$i
.endfor

.include <bsd.port.mk>
