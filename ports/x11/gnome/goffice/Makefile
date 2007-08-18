# $MirOS: ports/x11/gnome/libgnomeprint/Makefile,v 1.11 2007/07/05 21:00:51 bsiegert Exp $

COMMENT=		GNOME office components

VERSION=		0.4.2
DISTNAME=		goffice-${VERSION}
CATEGORIES=		x11/gnome devel

HOMEPAGE=		http://www.gnome.org/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/goffice/0.4/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS+=		::textproc/intltool
BUILD_DEPENDS+=		:p5-XML-Parser-*:textproc/p5-XML-Parser
LIB_DEPENDS+=		pcre::devel/pcre
LIB_DEPENDS+=		gnomeui-2::x11/gnome/libgnomeui
LIB_DEPENDS+=		gnomeprint-2-2::x11/gnome/libgnomeprint
LIB_DEPENDS+=		gsf-1,gsf-gnome-1::devel/libgsf,-gnome

USE_X11=		Yes
USE_CXX=		Yes # multiple dependencies
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--disable-gtk-doc
CONFIGURE_ARGS+=	--with-gtk
CONFIGURE_ARGS+=	--with-gnome

.include <bsd.port.mk>
