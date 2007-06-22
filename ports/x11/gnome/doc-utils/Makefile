# $MirOS: ports/x11/gnome/desktop/Makefile,v 1.4 2007/04/18 20:05:04 bsiegert Exp $

COMMENT=		GNOME documentation utilities

DISTNAME=		gnome-doc-utils-0.10.3
CATEGORIES=		x11 x11/gnome

HOMEPAGE=		http://www.gnome.org/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gnome-doc-utils/0.10/}

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS+=		::textproc/p5-XML-Parser
BUILD_DEPENDS+=		::textproc/intltool
B_R_DEPENDS+=		::lang/python/2.3,no_cxx
B_R_DEPENDS=		::textproc/scrollkeeper

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-gtk-doc
USE_GMAKE=		Yes

post-patch:
	@ln -s /usr/bin/true ${WRKDIR}/bin/scrollkeeper-update

.include <bsd.port.mk>
