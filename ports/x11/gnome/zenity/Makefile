# $MirOS: ports/x11/gnome/zenity/Makefile,v 1.5 2007/04/18 20:05:09 bsiegert Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/10/08 01:25:43 marcm Exp $

COMMENT=		dialogs for Gnome

DISTNAME=		zenity-1.6
CATEGORIES=		x11/gnome

HOMEPAGE=		http://www.gnome.org/


# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/zenity/1.6/}
EXTRACT_SUFX=		.tar.bz2

BUILD_DEPENDS=		:intltool-*:textproc/intltool \
			:scrollkeeper-*:textproc/scrollkeeper
MODULES+=		devel/pkgconfig

LIB_DEPENDS=		gconf-2::devel/gconf \
			gnomecanvas-2::x11/gnome/libgnomecanvas \

USE_GMAKE=		Yes
USE_X11=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

post-patch:
	@printf '#!/bin/sh\nexit 0\n' >${WRKDIR:Q}/bin/scrollkeeper-update
	@chmod +x ${WRKDIR:Q}/bin/scrollkeeper-update

.include <bsd.port.mk>
