# $MirOS: ports/x11/gnome/yelp/Makefile,v 1.4 2007/04/18 20:05:09 bsiegert Exp $
# $OpenBSD: Makefile,v 1.6 2004/02/22 05:33:55 marcm Exp $

BROKEN=			very old, new version needs mozilla devel package

COMMENT=		GNOME help browser

VERSION=		2.4.2
DISTNAME=		yelp-${VERSION}
CATEGORIES=		x11/gnome

HOMEPAGE=		http://www.gnome.org/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/yelp/2.4/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

RUN_DEPENDS=		:scrollkeeper->=0.3.6:textproc/scrollkeeper \
			:docbook-dsssl-*:textproc/docbook-dsssl
LIB_DEPENDS=		gnomeui-2::x11/gnome/libgnomeui \
			gtkhtml-2::x11/gnome/libgtkhtml \
			exslt::textproc/libxslt

USE_GMAKE=		Yes
USE_CXX=		Yes # fam, shared-mime-info
USE_X11=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

.include <bsd.port.mk>
