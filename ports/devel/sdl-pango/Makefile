# $MirOS: ports/devel/sdl-pango/Makefile,v 1.7 2007/02/22 22:57:50 tg Exp $

COMMENT=		SDL Pango fonts library
DISTNAME=		SDL_Pango-0.1.2
PKGNAME=		${DISTNAME:L:S/_/-/}-2
CATEGORIES=		devel graphics
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=sdlpango/}
MASTER_SITES0=		http://zarb.org/~gc/t/
HOMEPAGE=		http://sdlpango.sourceforge.net/

# LGPL 2.1
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

PATCHFILES=		SDL_Pango-0.1.2-API-adds.patch:0

MODULES+=		devel/pkgconfig
LIB_DEPENDS+=		SDL:sdl->=1.2.4:devel/sdl
LIB_DEPENDS+=		pango-1.0.0.0,pangoft2-1.0.0.0:pango->=1.2.0:devel/pango

USE_X11=		Yes # depends on SDL and pango, which need X11
CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static

.include <bsd.port.mk>
