# $MirOS: ports/x11/gnome/applets2/Makefile,v 1.10 2008/03/09 17:23:42 tg Exp $
# $OpenBSD: Makefile,v 1.19 2004/12/25 19:58:21 marcm Exp $

COMMENT=		applets for use with the GNOME panel
COMMENT-battstat=	GNOME applet for monitoring battery level

VERSION=		2.18.0
DISTNAME=		gnome-applets-${VERSION}
PKGNAME=		gnome-applets2-${VERSION}-${DASH_VER}
PKGNAME-battstat=	gnome-applets2-battstat-${VERSION}-${DASH_VER}
CATEGORIES=		x11 x11/gnome

HOMEPAGE=		http://www.gnome.org

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gnome-applets/2.18/}
EXTRACT_SUFX=           .tar.bz2

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS=		:scrollkeeper-*:textproc/scrollkeeper \
			:p5-XML-Parser-*:textproc/p5-XML-Parser
RUN_DEPENDS=		:scrollkeeper-*:textproc/scrollkeeper
LIB_DEPENDS=		panel-applet-2.0::x11/gnome/panel \
			gailutil.17::x11/gnome/gail \
			gtop-2.0.4.0::devel/libgtop \
			xklavier.11:libxklavier->=3.0:x11/libxklavier

FLAVOUR?=

PSEUDO_FLAVOURS=		no_battstat
# Only i386 and macppc have the headers for the battstat applet
.if ${MACHINE_ARCH} != "i386" && ${MACHINE_ARCH} != "powerpc"
FLAVOUR+=		no_battstat
.else
FLAVOUR?=
.endif

MULTI_PACKAGES=
.if ${FLAVOUR:L:Mno_battstat}
CONFIGURE_ARGS+=	--disable-battstat
.else
MULTI_PACKAGES+=	-battstat
.endif
SUBPACKAGE?=

USE_X11=		Yes
USE_CXX=		Yes # fam, libgtop, shared-mime-info
USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autoconf old
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--sysconfdir="${SYSCONFDIR}/gnome"
CONFIGURE_ARGS+=	--disable-schemas-install
CONFIGURE_ARGS+=	--with-gconf-schema-file-dir=${LOCALBASE}/share/schemas/gnome-applets2

.if defined(PACKAGING)
. if ${SUBPACKAGE} == "-battstat"
ONLY_FOR_PLATFORM=	*:*:i386 *:*:powerpc
LIB_DEPENDS=		panel-applet-2.0::x11/gnome/panel
. endif
.endif

post-patch:
	@printf '#!/bin/sh\nexit 0\n' >${WRKDIR:Q}/bin/scrollkeeper-update
	@chmod +x ${WRKDIR:Q}/bin/scrollkeeper-update

post-install:
	@${INSTALL_DATA_DIR} ${PREFIX}/share/examples/gnome-applets2; \
	cp -Rp ${WRKINST}/${SYSCONFDIR}/gnome/* ${PREFIX}/share/examples/gnome-applets2/

.include <bsd.port.mk>
