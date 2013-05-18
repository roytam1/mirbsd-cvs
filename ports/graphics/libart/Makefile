# $OpenBSD: Makefile,v 1.12 2004/02/21 22:27:49 marcm Exp $

COMMENT=		"high-performance 2D graphics library"

VERSION=		2.3.16
DISTNAME=		libart_lgpl-${VERSION}
PKGNAME=		libart-${VERSION}-0
CATEGORIES=		graphics

HOMEPAGE=		http://www.artofcode.com/libart.html


# lgpl
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/libart_lgpl/2.3/}

CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+= 	${CONFIGURE_SHARED}

.include <bsd.port.mk>
