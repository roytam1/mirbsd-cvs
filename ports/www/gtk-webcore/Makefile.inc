# $MirOS: ports/www/gtk-webcore/Makefile.inc,v 1.2 2006/02/09 11:15:34 tg Exp $

VERSION=		0.5.0
CATEGORIES=		www x11 x11/gnome

HOMEPAGE=		http://gtk-webcore.sourceforge.net
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=gtk-webcore/}

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS+=		xml2::textproc/libxml
MODULES+=		devel/pkgconfig

USE_X11=		Yes
CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes
USE_CXX=		Yes

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
