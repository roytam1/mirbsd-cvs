# $MirOS: ports/x11/gnome/keyring/Makefile,v 1.3 2005/12/29 18:26:01 bsiegert Exp $
# $OpenBSD: Makefile,v 1.4 2004/12/15 13:57:56 alek Exp $

COMMENT=			password agent for the GNOME project

DISTNAME=		gnome-keyring-0.4.6
CATEGORIES=		x11/gnome

HOMEPAGE=		http://www.gnome.org/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gnome-keyring/0.4/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

LIB_DEPENDS=		gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-gtk-doc

.include <bsd.port.mk>
