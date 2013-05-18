# $MirOS: ports/x11/libxklavier/Makefile,v 1.1.7.1 2005/03/18 16:00:42 tg Exp $

COMMENT=		"X Keyboard Extension library"

VERSION=		2.0
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

MODULES=		devel/gettext devel/pkgconfig

USE_X11=		Yes
CONFIGURE_STYLE= 	autogen
AUTOCONF_NEW=		Yes

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

.include <bsd.port.mk>
