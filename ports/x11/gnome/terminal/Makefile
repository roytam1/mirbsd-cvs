# $MirOS: ports/x11/gnome/terminal/Makefile,v 1.6 2007/06/26 20:34:32 bsiegert Exp $
# $OpenBSD: Makefile,v 1.14 2004/12/15 13:57:57 alek Exp $

COMMENT=		GNOME terminal

DISTNAME=		gnome-terminal-2.18.1
CATEGORIES=		x11/gnome

HOMEPAGE=		http://www.gnome.org/


# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gnome-terminal/2.18/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS=		:p5-XML-Parser-*:textproc/p5-XML-Parser \
			:scrollkeeper->=0.3.12:textproc/scrollkeeper
RUN_DEPENDS=		:scrollkeeper->=0.3.12:textproc/scrollkeeper
LIB_DEPENDS=		gnomeui-2::x11/gnome/libgnomeui \
			startup-notification-1::devel/startup-notification \
			vte::devel/vte

USE_X11=		Yes
USE_CXX=		Yes # fam, shared-mime-info
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-gtk-doc
CONFIGURE_ARGS+=	--with-widget=vte
CONFIGURE_ARGS+=	--disable-schemas-install
CONFIGURE_ARGS+=	--with-gconf-schema-file-dir=${LOCALBASE}/share/schemas/gnome-terminal

post-patch:
	@printf '#!/bin/sh\nexit 0\n' >${WRKDIR:Q}/bin/scrollkeeper-update
	@chmod +x ${WRKDIR:Q}/bin/scrollkeeper-update

.include <bsd.port.mk>
