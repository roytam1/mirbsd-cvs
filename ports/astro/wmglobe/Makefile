# $MirOS$
# $OpenBSD: Makefile,v 1.14 2002/09/17 15:22:26 wilfried Exp $

COMMENT=		'wm-dockapp; displays the earth on an icon'
DISTNAME=		wmglobe-1.3
CATEGORIES=		astro x11 x11/windowmaker
HOMEPAGE=		http://perso.linuxfr.org/jdumont/wmg/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}

LIB_DEPENDS=		jpeg::graphics/jpeg \
			tiff::graphics/tiff \
			png::graphics/png \
			ungif::graphics/libungif \
			wraster::x11/windowmaker

USE_X11=		Yes
USE_CXX=		Yes
NO_REGRESS=		Yes

.include <bsd.port.mk>
