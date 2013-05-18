# $MirOS: ports/devel/fox/Makefile,v 1.2 2005/07/06 19:21:29 bsiegert Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/11/13 18:50:39 espie Exp $

COMMENT=		'C++ toolkit for GUI'

CATEGORIES=		devel x11
VERSION=		1.1.41
DASH_VER=		-0
DISTNAME=		fox-${VERSION}
PKGNAME=		${DISTNAME}${DASH_VER}
HOMEPAGE=		http://www.fox-toolkit.org/
MASTER_SITES=		${HOMEPAGE}/ftp/

# LGPL or looser
PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes

LIB_DEPENDS=		bz2::archivers/bzip2 \
			jpeg::graphics/jpeg \
			tiff::graphics/tiff
MODULES+=		graphics/png

USE_CXX=		Yes
USE_X11=		Yes
CONFIGURE_STYLE=	autoconf no-autoheader
CONFIGURE_ARGS+=	--x-includes=${X11BASE}/include \
			--x-libraries=${X11BASE}/lib

.include <bsd.port.mk>
