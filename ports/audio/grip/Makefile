# $MirOS: ports/audio/grip/Makefile,v 1.5 2007/04/04 18:00:24 bsiegert Exp $
# $OpenBSD: Makefile,v 1.8 2002/12/29 19:29:56 fgsch Exp $

COMMENT=		front-end to external cd audio rippers and mp3 encoders
V=			3.2.0
DISTNAME=		grip-${V}
CATEGORIES=		audio
EXTRACT_SUFX=		.tar.gz
HOMEPAGE=		http://www.nostatic.org/grip/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=grip/}

LIB_DEPENDS=	ghttp::www/libghttp \
		id3::audio/id3lib \
		glib-2.0.0.0::devel/glib \
		gnomeui-2::x11/gnome/libgnomeui \
		curl::net/curl \
		vte::devel/vte
MODULES+=		devel/pkgconfig

USE_X11=		Yes
USE_GMAKE=		Yes
USE_CXX=		Yes
NO_REGRESS=		Yes

AUTOCONF_NEW=		Yes
CONFIGURE_STYLE=	autoconf
CONFIGURE_ENV=		LIBS="-pthread"

CONFIGURE_ARGS+=	--disable-cdpar

.include <bsd.port.mk>
