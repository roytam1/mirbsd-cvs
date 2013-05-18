# $MirOS: ports/x11/gnome/nautilus/Makefile,v 1.2 2006/02/09 11:15:46 tg Exp $
# $OpenBSD: Makefile,v 1.13 2004/12/15 13:57:57 alek Exp $

COMMENT=			GNOME shell and file manager

DISTNAME=		nautilus-2.8.2
CATEGORIES=		x11 x11/gnome

HOMEPAGE=		http://www.gnome.org/projects/nautilus/

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/nautilus/2.8/}
EXTRACT_SUFX=           .tar.bz2

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS=		:p5-XML-Parser-*:textproc/p5-XML-Parser
LIB_DEPENDS=		eel-2.10.2::x11/gnome/eel \
			gnome-desktop-2.0::x11/gnome/desktop \
			rsvg-2.2::x11/gnome/librsvg
RUN_DEPENDS=		:gnome-icon-theme-*:x11/gnome/icon-theme

USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autoconf old
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+= 	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--sysconfdir="${SYSCONFDIR}/gnome"
CONFIGURE_ARGS+=	--with-gconf-schema-file-dir=${LOCALBASE}/share/schemas/nautilus
CONFIGURE_ENV=		CPPFLAGS="-I${LOCALBASE}/include -DWEB_NAVIGATION_ENABLED" \
			LDFLAGS="-L${WRKBUILD}/libnautilus/.libs \
				-L${WRKBUILD}/libnautilus-adapter/.libs \
				-L${WRKBUILD}/libnautilus-private/.libs \
				-L${LOCALBASE}/lib"

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/nautilus; 

.include <bsd.port.mk>
