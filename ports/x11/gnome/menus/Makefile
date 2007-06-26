# $MirOS: ports/x11/gnome/desktop/Makefile,v 1.5 2007/06/22 23:06:32 bsiegert Exp $
# $OpenBSD: Makefile,v 1.11 2004/12/15 13:57:56 alek Exp $

COMMENT=		GNOME menu package implementing the fd.o menu spec

DISTNAME=		gnome-menus-2.18.2
CATEGORIES=		x11 x11/gnome

HOMEPAGE=		http://www.gnome.org/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gnome-menus/2.18/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

LIB_DEPENDS+=		fam::sysutils/fam
LIB_DEPENDS+=		glib-2.0.0.0::devel/glib

CONFIGURE_STYLE=	autoconf
USE_X11=		Yes
USE_CXX=		Yes # fam, libgtop, shared-mime-info
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static
CONFIGURE_ARGS+=	--disable-gtk-doc
CONFIGURE_ARGS+=	--enable-python=no
USE_GMAKE=		Yes

post-install:
	mkdir ${PREFIX}/share/examples/gnome-menus
	mv ${WRKINST}/etc/xdg/menus/* ${PREFIX}/share/examples/gnome-menus

.include <bsd.port.mk>
