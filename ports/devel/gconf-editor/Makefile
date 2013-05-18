# $MirOS: ports/devel/gconf-editor/Makefile,v 1.1.7.1 2005/03/18 15:44:37 tg Exp $

COMMENT=		"editor for the GConf configuration system"
DISTNAME=		gconf-editor-2.4.0
CATEGORIES=		devel x11/gnome
HOMEPAGE=		http://www.gnome.org/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gconf-editor/2.4/}
EXTRACT_SUFX=		.tar.bz2

LIB_DEPENDS=		gconf-2::devel/gconf2
MODULES+=		devel/pkgconfig

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		yes
CONFIGURE_ARGS+=	--disable-gtk-doc

.include <bsd.port.mk>
