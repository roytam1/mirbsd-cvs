# $MirOS$
# $OpenBSD: Makefile,v 1.11 2004/02/01 20:17:47 sturm Exp $

COMMENT=		themes and icons for Window Maker

DISTNAME=		WindowMaker-extra-0.1
PKGNAME=		${DISTNAME:L}-0
CATEGORIES=		x11 x11/windowmaker

HOMEPAGE=		http://www.windowmaker.org/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_WINDOWMAKER:=source/release/}

RUN_DEPENDS=		:windowmaker-*:x11/windowmaker

USE_X11=		Yes
USE_CXX=		Yes # depends on windowmaker, which uses CXX
NO_REGRESS=		Yes

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS=		--prefix="${PREFIX}"

NO_BUILD=		Yes
PKG_ARCH=		*

.include <bsd.port.mk>
