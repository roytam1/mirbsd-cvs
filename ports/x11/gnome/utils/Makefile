# $MirOS: ports/x11/gnome/utils/Makefile,v 1.5 2007/07/31 20:33:38 bsiegert Exp $
# $OpenBSD: Makefile,v 1.3 2003/12/01 04:13:07 marcm Exp $

COMMENT=		GNOME utility programs

DISTNAME=		gnome-utils-2.18.1
CATEGORIES=		x11/gnome

HOMEPAGE=		http://www.gnome.org/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gnome-utils/2.18/}
EXTRACT_SUFX=		.tar.bz2

LIB_DEPENDS+=		gnomeui-2::x11/gnome/libgnomeui
LIB_DEPENDS+=		panel-applet-2::x11/gnome/panel
LIB_DEPENDS+=		gnomeprintui-2-2::x11/gnome/libgnomeprintui
LIB_DEPENDS+=		gtop-2.0.0.0::devel/libgtop
MODULES+=		devel/pkgconfig

USE_X11=		Yes
USE_CXX=		Yes # fam, shared-mime-info
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--with-gconf-schema-file-dir=${LOCALBASE}/share/schemas/gnome-utils
CONFIGURE_ARGS+=	--disable-hal
CONFIGURE_ARGS+=	--enable-ipv6=yes

post-patch:
	@printf '#!/bin/sh\nexit 0\n' >${WRKDIR:Q}/bin/scrollkeeper-update
	@chmod +x ${WRKDIR:Q}/bin/scrollkeeper-update

.include <bsd.port.mk>
