# $MirOS: ports/x11/gnome/panel/Makefile,v 1.6 2007/06/26 16:54:49 bsiegert Exp $
# $OpenBSD: Makefile,v 1.15 2004/12/30 04:25:06 marcm Exp $

COMMENT=		GNOME panel

VERSION=		2.18.2
DISTNAME=		gnome-panel-${VERSION}
PKGNAME=		${DISTNAME}-${DASH_VER}
CATEGORIES=		x11 x11/gnome

HOMEPAGE=		http://www.gnome.org

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gnome-panel/2.18/}
EXTRACT_SUFX=           .tar.bz2

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		devel/gettext devel/pkgconfig graphics/png

BUILD_DEPENDS+=		:p5-XML-Parser-*:textproc/p5-XML-Parser
B_R_DEPENDS+=		:scrollkeeper->=0.3.12:textproc/scrollkeeper
LIB_DEPENDS+= 		gnome-desktop-2.0::x11/gnome/desktop
LIB_DEPENDS+= 		wnck-1.4::devel/libwnck
LIB_DEPENDS+= 		gnome-menu::x11/gnome/menus
LIB_DEPENDS+=		camel-1.2.0.0,ebook-1.2.0.0,ecal-1.2.0.0,edataserver-1.2.0.0,edataserverui-1.2.0.0::x11/gnome/evolution-data-server

USE_X11=		Yes
USE_CXX=		Yes # fam, shared-mime-info
USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+= 	--disable-gtk-doc
CONFIGURE_ARGS+= 	--enable-eds=yes
CONFIGURE_ARGS+= 	--with-gconf-schema-file-dir=${LOCALBASE}/share/schemas/gnome-panel

post-patch:
	@printf '#!/bin/sh\nexit 0\n' >${WRKDIR:Q}/bin/scrollkeeper-update
	@chmod +x ${WRKDIR:Q}/bin/scrollkeeper-update

.include <bsd.port.mk>
