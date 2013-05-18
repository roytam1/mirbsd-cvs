# $MirOS: ports/devel/libuta/Makefile,v 1.1.7.1 2005/03/18 15:44:55 tg Exp $
# $OpenBSD: Makefile,v 1.13 2004/01/04 20:32:29 pvalchev Exp $

COMMENT=	"graphical user interface library for C++"
VERSION=	0.4.4
DISTNAME=	libuta-${VERSION}
CATEGORIES=	devel
HOMEPAGE=	http://libuta.sourceforge.net/

PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=libuta/}

LIB_DEPENDS=	smpeg.1.3::devel/smpeg \
		SDL_mixer::devel/sdl-mixer \
		sigc.0.0::devel/libsigc++
MODULES+=	graphics/png print/freetype

USE_X11=	Yes
USE_CXX=	Yes

CONFIGURE_STYLE= autoconf
CONFIGURE_ARGS=	${CONFIGURE_SHARED}

VMEM_WARNING=	Yes

.include <bsd.port.mk>
