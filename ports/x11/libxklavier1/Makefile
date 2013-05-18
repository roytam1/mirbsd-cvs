# $MirOS: ports/x11/libxklavier1/Makefile,v 1.3 2006/09/14 00:15:28 tg Exp $

COMMENT=		X Keyboard Extension library

VERSION=		1.04
DISTNAME=		libxklavier-${VERSION}
DASH_VER=		1
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

MODULES=		devel/gettext devel/pkgconfig converters/libiconv
USE_ICONV=		any oldm4

USE_X11=		Yes
CONFIGURE_STYLE= 	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

.include <bsd.port.mk>
