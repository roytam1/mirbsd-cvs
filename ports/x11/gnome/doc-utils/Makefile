# $MirOS: ports/x11/gnome/doc-utils/Makefile,v 1.4 2008/08/26 17:17:39 tg Exp $

COMMENT=		GNOME documentation utilities

DISTNAME=		gnome-doc-utils-0.10.3
DASH_VER=		3
CATEGORIES=		x11 x11/gnome

HOMEPAGE=		http://www.gnome.org/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gnome-doc-utils/0.10/}

MODULES+=		devel/gettext
MODULES+=		devel/pkgconfig

BUILD_DEPENDS+=		::textproc/p5-XML-Parser
BUILD_DEPENDS+=		::textproc/intltool
B_R_DEPENDS+=		:libxml->=2.6.32:textproc/libxml
B_R_DEPENDS+=		::textproc/scrollkeeper

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-gtk-doc
USE_GMAKE=		Yes

post-patch:
	@printf '#!/bin/sh\nexit 0\n' >${WRKDIR:Q}/bin/scrollkeeper-update
	@chmod +x ${WRKDIR:Q}/bin/scrollkeeper-update

.include <bsd.port.mk>
