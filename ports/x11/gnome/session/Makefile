# $MirOS: ports/x11/gnome/session/Makefile,v 1.4 2007/04/18 20:05:08 bsiegert Exp $
# $OpenBSD: Makefile,v 1.13 2004/12/15 13:57:57 alek Exp $

COMMENT=		GNOME session

DISTNAME=		gnome-session-2.18.2
CATEGORIES=		x11 x11/gnome

HOMEPAGE=		http://www.gnome.org

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gnome-session/2.18/}
EXTRACT_SUFX=           .tar.bz2

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS+=		:p5-XML-Parser-*:textproc/p5-XML-Parser
BUILD_DEPENDS+=		:scrollkeeper-*:textproc/scrollkeeper
LIB_DEPENDS+=		startup-notification-1::devel/startup-notification
LIB_DEPENDS+= 		gnomeui-2.0::x11/gnome/libgnomeui
LIB_DEPENDS+=		gnome-desktop-2::x11/gnome/desktop

USE_X11=		Yes
USE_CXX=		Yes # fam, shared-mime-info
USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+= 	--disable-rebuilds
CONFIGURE_ARGS+=	--with-gconf-schema-file-dir=${LOCALBASE}/share/schemas/gnome-session

post-patch:
	@ln -s $$(whence -p true) ${WRKDIR}/bin/scrollkeeper-update

.include <bsd.port.mk>
