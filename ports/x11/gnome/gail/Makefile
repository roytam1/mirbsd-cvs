# $MirOS: ports/x11/gnome/gail/Makefile,v 1.2 2006/02/09 09:36:22 tg Exp $
# $OpenBSD: Makefile,v 1.9 2004/12/15 13:57:56 alek Exp $

COMMENT=		"GNOME Accessibility Implementation Library"

DISTNAME=		gail-1.8.1
CATEGORIES=		devel x11/gnome

HOMEPAGE=		http://www.gnome.org

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gail/1.8/}
EXTRACT_SUFX=           .tar.bz2

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		devel/gettext devel/pkgconfig

LIB_DEPENDS= 		atk-1.0.800.0::devel/atk \
			gnomecanvas-2::x11/gnome/libgnomecanvas

USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		yes
CONFIGURE_ARGS+= 	--disable-rebuilds
CONFIGURE_ARGS+= 	--disable-gtk-doc

.include <bsd.port.mk>
