# $MirOS: ports/x11/gnome/controlcenter2/Makefile,v 1.4 2007/04/18 20:05:04 bsiegert Exp $
# $OpenBSD: Makefile,v 1.12 2004/12/15 13:57:56 alek Exp $

COMMENT=		GNOME control center

VERSION=		2.18.1
DISTNAME=		control-center-${VERSION}
CATEGORIES=		x11 x11/gnome
HOMEPAGE=		http://www.gnome.org/


MASTER_SITES=		${MASTER_SITE_GNOME:=sources/control-center/2.18/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

LIB_DEPENDS+=		gnomekbd,gnomekbdui::x11/gnome/libgnomekbd
LIB_DEPENDS+=		metacity-private::x11/gnome/metacity
LIB_DEPENDS+=		nautilus-extension::x11/gnome/nautilus
LIB_DEPENDS+=		panel-applet-2::x11/gnome/panel
BUILD_DEPENDS=		:p5-XML-Parser-*:textproc/p5-XML-Parser
B_R_DEPENDS+=		::devel/desktop-file-utils

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
USE_CXX=		Yes # fam, shared-mime-info, cups, libgsf
USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autogen old
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	--sysconfdir="${SYSCONFDIR}/gnome"
CONFIGURE_ARGS+=	--with-gconf-schema-file-dir=${LOCALBASE}/share/schemas/control-center2
CONFIGURE_ARGS+=	--disable-gstreamer
CONFIGURE_ARGS+=	--disable-hal

post-patch:
	ln -s $$(whence -p true) ${WRKDIR}/bin/scrollkeeper-update

post-install:
	@${INSTALL_DATA_DIR} ${PREFIX}/share/examples/controlcenter2; \
	cp -Rp ${WRKINST}/${SYSCONFDIR}/gnome/* ${PREFIX}/share/examples/controlcenter2/

.include <bsd.port.mk>
