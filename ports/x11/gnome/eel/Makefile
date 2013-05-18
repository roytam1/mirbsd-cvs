# $MirOS: ports/x11/gnome/eel/Makefile,v 1.4 2007/04/18 20:05:04 bsiegert Exp $
# $OpenBSD: Makefile,v 1.12 2004/12/15 13:57:56 alek Exp $

COMMENT=		Eazel Extensions Library

DISTNAME=		eel-2.18.3
CATEGORIES=		devel x11/gnome

HOMEPAGE=		http://www.gnome.org

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/eel/2.18/}
EXTRACT_SUFX=           .tar.bz2

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS+=		::textproc/intltool
BUILD_DEPENDS+=		::textproc/p5-XML-Parser
LIB_DEPENDS+=		startup-notification-1::devel/startup-notification
LIB_DEPENDS+=		gnomeui-2.0::x11/gnome/libgnomeui
LIB_DEPENDS+=		gailutil.17::x11/gnome/gail
LIB_DEPENDS+=		gnome-desktop-2::x11/gnome/desktop
LIB_DEPENDS+=		gnome-menu::x11/gnome/menus


USE_X11=		Yes
USE_CXX=		Yes # fam, shared-mime-info
USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+= 	${CONFIGURE_SHARED}

.include <bsd.port.mk>
