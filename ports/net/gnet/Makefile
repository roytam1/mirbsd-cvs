# $OpenBSD: Makefile,v 1.5 2004/02/25 01:35:50 naddy Exp $

COMMENT=			simple network library
DISTNAME=	gnet-2.0.4
CATEGORIES=	net
MASTER_SITES=	${HOMEPAGE}src/

HOMEPAGE=	http://www.gnetlibrary.org/

# LGPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MODULES=	devel/gettext devel/pkgconfig

LIB_DEPENDS=	glib-2.0.0.0,gthread-2.0.0.0::devel/glib

USE_CXX=	Yes
CONFIGURE_STYLE=gnu
CONFIGURE_ARGS+=${CONFIGURE_SHARED} \
	--enable-threadsafe-getaddrinfo --enable-threadsafe-gethostbyname

.include <bsd.port.mk>
