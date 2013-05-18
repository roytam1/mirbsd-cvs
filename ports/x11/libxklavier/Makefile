# $MirOS: ports/x11/libxklavier/Makefile,v 1.3 2006/09/14 00:15:28 tg Exp $

COMMENT=		X Keyboard Extension library

VERSION=		3.2
DISTNAME=		libxklavier-${VERSION}
CATEGORIES=		x11 x11/gnome

HOMEPAGE=		http://www.freedesktop.org/Software/LibXklavier
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=gswitchit/}

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS+=		xml2::textproc/libxml
LIB_DEPENDS+=		glib-2.0.0.0,gobject-2.0.0.0::devel/glib

MODULES=		devel/gettext devel/pkgconfig

USE_X11=		Yes
CONFIGURE_STYLE= 	autogen
AUTOCONF_NEW=		Yes
USE_ICONV=		any oldm4

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

.include <bsd.port.mk>
