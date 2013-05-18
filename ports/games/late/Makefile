# $OpenBSD: Makefile,v 1.4 2004/02/25 02:35:16 naddy Exp $

COMMENT=			puzzle game resembling the arcade game Qix
DISTNAME=	late-0.0.3
EXTRACT_SUFX=	.tar.bz2
CATEGORIES=	games x11
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=late/}

HOMEPAGE=	http://late.sourceforge.net/

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

LIB_DEPENDS=	SDL_image::devel/sdl-image

USE_X11=	Yes
USE_CXX=	Yes

CONFIGURE_STYLE=gnu

.include <bsd.port.mk>
