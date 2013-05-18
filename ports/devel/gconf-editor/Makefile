# $MirOS: ports/devel/gconf-editor/Makefile,v 1.5 2007/04/07 14:32:26 bsiegert Exp $

COMMENT=		editor for the GConf configuration system
DISTNAME=		gconf-editor-2.18.0
CATEGORIES=		devel x11/gnome
HOMEPAGE=		http://www.gnome.org/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gconf-editor/2.18/}
EXTRACT_SUFX=		.tar.bz2

LIB_DEPENDS+=		gconf-2::devel/gconf
LIB_DEPENDS+=		gnome-2::x11/gnome/libgnome
LIB_DEPENDS+=		gnomeui-2::x11/gnome/libgnomeui
MODULES+=		devel/pkgconfig

USE_X11=		Yes
USE_CXX=		Yes # fam, shared-mime-info
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		yes
CONFIGURE_ARGS+=	--disable-gtk-doc

post-patch:
	ln -s $$(whence -p true) ${WRKDIR}/bin/scrollkeeper-update

.include <bsd.port.mk>
