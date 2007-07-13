# $MirOS: ports/x11/gnome/libgnomeprint/Makefile,v 1.11 2007/07/05 21:00:51 bsiegert Exp $
# $OpenBSD: Makefile,v 1.9 2004/12/15 13:57:56 alek Exp $

COMMENT=		keyboard management APIs for GNOME

VERSION=		2.18.2
DISTNAME=		libgnomekbd-${VERSION}
CATEGORIES=		x11/gnome devel

HOMEPAGE=		http://www.gnome.org/projects/gnome-print/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/libgnomekbd/2.18/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS=		:p5-XML-Parser-*:textproc/p5-XML-Parser
LIB_DEPENDS+=		dbus-glib-1::sysutils/dbus-glib
LIB_DEPENDS+=		gnome-2::x11/gnome/libgnome
LIB_DEPENDS+=		gnomeui-2::x11/gnome/libgnomeui
LIB_DEPENDS+=		gnome-keyring::x11/gnome/keyring
LIB_DEPENDS+=		xklavier::x11/libxklavier


USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--disable-gtk-doc
CONFIGURE_ARGS+=	--with-gconf-schema-file-dir=${LOCALBASE}/share/schemas/libgnomekbd


.include <bsd.port.mk>
