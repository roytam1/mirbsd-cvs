# $MirOS: ports/games/freeciv/Makefile,v 1.3 2006/09/14 00:09:24 tg Exp $
# $OpenBSD: Makefile,v 1.34 2004/05/04 11:31:48 naddy Exp $

COMMENT=			Civilization clone for X11; multiplayer

DISTNAME=	freeciv-2.0.0
CATEGORIES=	games
HOMEPAGE=	http://www.freeciv.org/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.freeciv.org/pub/freeciv/stable/
EXTRACT_SUFX=	.tar.bz2

FLAVOURS=	gtk1 xaw esd sdl
FLAVOUR?=

MODULES=	devel/gettext

.if ${FLAVOUR:L:Mgtk1} && ${FLAVOUR:L:Mxaw}
ERRORS+=	"Fatal: Conflicting flavours: gtk1, xaw"
.endif

.if ${FLAVOUR:L:Mgtk1}
LIB_DEPENDS+=	Imlib.19,gdk_imlib::graphics/imlib
USE_CXX=	Yes
CONFIGURE_ARGS+=--enable-client=gtk
.elif ${FLAVOUR:L:Mxaw}
CONFIGURE_ARGS+=--enable-client=xaw
.else
CONFIGURE_ARGS+=--enable-client=gtk2
LIB_DEPENDS+=	gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+
.endif

.if ${FLAVOUR:L:Msdl}
LIB_DEPENDS+=	SDL_mixer::devel/sdl-mixer
CONFIGURE_ARGS+=	--with-sdl-prefix=${LOCALBASE}
.else
CONFIGURE_ARGS+=	--disable-sdl-mixer
.endif

.if ${FLAVOUR:L:Mesd}
LIB_DEPENDS+=	esd.2::audio/esound
CONFIGURE_ARGS+=	--with-esd-prefix=${LOCALBASE}
.else
CONFIGURE_ARGS+=	--disable-esd
.endif

USE_X11=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes


.include <bsd.port.mk>
