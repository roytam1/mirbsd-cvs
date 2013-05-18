# $MirOS: ports/x11/gnome/libgnomeprintui/Makefile,v 1.3 2006/02/09 09:36:23 tg Exp $
# $OpenBSD: Makefile,v 1.8 2004/12/15 13:57:56 alek Exp $

COMMENT=		"user interface components for libgnomeprint"
DISTNAME=		libgnomeprintui-2.8.1
CATEGORIES=		x11/gnome devel
HOMEPAGE=		http://www.gnome.org/projects/gnome-print/


# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/libgnomeprintui/2.8/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS=		:libglade2->=2.0.0:devel/libglade \
			:gnome-icon-theme->=1.2.0:x11/gnome/icon-theme
RUN_DEPENDS=		:gnome-icon-theme->=1.2.0:x11/gnome/icon-theme
LIB_DEPENDS=		gnomecanvas-2::x11/gnome/libgnomecanvas \
			gnomeprint-2-2::x11/gnome/libgnomeprint

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--disable-gtk-doc

.include <bsd.port.mk>
