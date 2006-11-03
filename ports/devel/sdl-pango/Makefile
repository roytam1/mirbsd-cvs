# $MirOS: ports/devel/sdl-ttf/Makefile,v 1.8 2006/11/03 22:02:00 tg Exp $

COMMENT=		SDL Pango fonts library
DISTNAME=		SDL_Pango-0.1.2
PKGNAME=		${DISTNAME:L:S/_/-/}-0
CATEGORIES=		devel graphics
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=sdlpango/}
HOMEPAGE=		http://sdlpango.sourceforge.net/

# LGPL 2.1
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MODULES+=		devel/pkgconfig
LIB_DEPENDS+=		SDL:sdl->=1.2.4:devel/sdl
# XXX this STINKS, we'd better not give any shlib version
LIB_DEPENDS+=		pango-1.0.0.0,pangoft2-1.0.0.0:pango->=1.2.0:devel/pango

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--disable-dependency-tracking \
			--disable-libtool-lock

.include <bsd.port.mk>
