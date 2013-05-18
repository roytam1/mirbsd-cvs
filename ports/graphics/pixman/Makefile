# $MirOS: ports/graphics/pixman/Makefile,v 1.1 2008/08/25 14:51:36 bsiegert Exp $

COMMENT=		pixel manipulation library

DISTNAME=		pixman-0.11.8
CATEGORIES=		graphics
EXTRACT_SUFX=		.tar.bz2

HOMEPAGE=		http://cairographics.org/introduction

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

# distfile is no longer available upstream
#MASTER_SITES=		http://cairographics.org/releases/
MASTER_SITES=		http://distfiles.ber.de.eu.finkmirrors.net/

MODULES+=		devel/pkgconfig

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

.include <bsd.port.mk>
