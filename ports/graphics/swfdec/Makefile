# $MirOS: ports/graphics/swfdec/Makefile,v 1.3 2006/02/09 11:11:52 tg Exp $
# $OpenBSD: Makefile,v 1.4 2003/12/10 21:28:58 naddy Exp $

COMMENT=			flash rendering library
DISTNAME=	swfdec-0.2.2
CATEGORIES=	graphics www/mozilla
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=swfdec/}

HOMEPAGE=	http://swfdec.sourceforge.net/


# LGPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

LIB_DEPENDS=	SDL::devel/sdl \
		mad.2::audio/libmad \
		art_lgpl_2.5::graphics/libart \
		gdk-x11-2.0.0.11,gdk_pixbuf-2.0.0.11,gtk-x11-2.0.0.11::x11/gtk+
MODULES+=		devel/pkgconfig

USE_CXX=	Yes

CONFIGURE_STYLE=gnu
CONFIGURE_ARGS+=--disable-pixbuf-loader

FLAVORS=	plugin
FLAVOR?=

.if ${FLAVOR:L:Mplugin}
BROKEN=		no mozilla package in MirPorts
MOZ=mozilla
BUILD_DEPENDS=	:mozilla-devel->=1.4:www/mozilla,-devel
CFLAGS+=	-DMOZ_X11
PORTPATH+=	${WRKDIR}/bin:/usr/bin:/bin:/usr/sbin:/sbin:${LOCALBASE}/bin:${X11BASE}/bin:${LOCALBASE}/${MOZ}
.endif

.include <bsd.port.mk>
