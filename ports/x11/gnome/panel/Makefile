# $MirOS: ports/x11/gnome/panel/Makefile,v 1.3 2006/02/09 11:15:46 tg Exp $
# $OpenBSD: Makefile,v 1.15 2004/12/30 04:25:06 marcm Exp $

COMMENT=			GNOME panel

VERSION=		2.8.2
DISTNAME=		gnome-panel-${VERSION}
PKGNAME=		${DISTNAME}-1
CATEGORIES=		x11 x11/gnome

HOMEPAGE=		http://www.gnome.org

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gnome-panel/2.8/}
EXTRACT_SUFX=           .tar.bz2

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		devel/gettext devel/pkgconfig graphics/png

BUILD_DEPENDS=		:p5-XML-Parser-*:textproc/p5-XML-Parser \
			:scrollkeeper->=0.3.12:textproc/scrollkeeper
RUN_DEPENDS=		:scrollkeeper->=0.3.12:textproc/scrollkeeper
LIB_DEPENDS= 		gnome-desktop-2.0::x11/gnome/desktop \
			wnck-1.4::devel/libwnck \
			ecal,edataserver::x11/gnome/evolution-data-server

USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+= 	--disable-gtk-doc
CONFIGURE_ARGS+= 	--enable-eds=yes
CONFIGURE_ARGS+= 	--with-gconf-schema-file-dir=${LOCALBASE}/share/schemas/gnome-panel

post-patch:
	@ln -s /usr/bin/true ${WRKDIR}/bin/scrollkeeper-update

.include <bsd.port.mk>
