# $OpenBSD: Makefile,v 1.2 2003/05/12 08:23:46 jolan Exp $

COMMENT=			simple library designed for DVD navigation

DISTNAME=	libdvdplay-1.0.1
PKGNAME=	${DISTNAME}-2
CATEGORIES=	devel
MASTER_SITES=	http://www.videolan.org/pub/libdvdplay/1.0.1/

HOMEPAGE=	http://developers.videolan.org/libdvdplay/


# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

LIB_DEPENDS=	dvdread::devel/libdvdread

CONFIGURE_ARGS+=${CONFIGURE_SHARED}

CONFIGURE_STYLE=autoconf
AUTOCONF_NEW=	Yes

.include <bsd.port.mk>
