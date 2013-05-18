# $MirOS: ports/x11/gnome/desktop/Makefile,v 1.5 2007/06/22 23:06:32 bsiegert Exp $
# $OpenBSD: Makefile,v 1.11 2004/12/15 13:57:56 alek Exp $

COMMENT=		components for the GNOME desktop

DISTNAME=		gnome-desktop-2.18.2
CATEGORIES=		x11 x11/gnome

HOMEPAGE=		http://www.gnome.org/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gnome-desktop/2.18/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS=		:p5-XML-Parser-*:textproc/p5-XML-Parser \
			:scrollkeeper-*:textproc/scrollkeeper
RUN_DEPENDS=		:scrollkeeper-*:textproc/scrollkeeper
LIB_DEPENDS=		gnomeui-2::x11/gnome/libgnomeui \
			startup-notification-1::devel/startup-notification
B_R_DEPENDS+=		::x11/gnome/doc-utils

CONFIGURE_STYLE=	autoconf
USE_X11=		Yes
USE_CXX=		Yes # fam, libgtop, shared-mime-info
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--disable-gtk-doc
CONFIGURE_ARGS+=	--with-gnome-distributor="MirPorts"
USE_GMAKE=		Yes

post-patch:
	@printf '#!/bin/sh\nexit 0\n' >${WRKDIR:Q}/bin/scrollkeeper-update
	@chmod +x ${WRKDIR:Q}/bin/scrollkeeper-update

.include <bsd.port.mk>
