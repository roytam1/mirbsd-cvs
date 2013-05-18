# $MirOS: ports/misc/xcdroast/Makefile,v 1.3 2005/07/07 21:23:54 bsiegert Exp $
# $OpenBSD: Makefile,v 1.8 2004/01/12 05:37:11 jolan Exp $

COMMENT=		"gtk-based frontend to cdrtools"
DISTNAME=		xcdroast-0.98alpha15
PKGNAME=		${DISTNAME:L:S/alpha/a/}-1
CATEGORIES=		misc x11
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=xcdroast/}

HOMEPAGE=		http://www.xcdroast.org/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=	Yes

MODULES=	devel/gettext devel/pkgconfig

RUN_DEPENDS=	:cdrtools->=2.0:sysutils/cdrtools
LIB_DEPENDS=	gdk_pixbuf-2.0.0.14,gdk-x11-2.0.0.14,gtk-x11-2.0.0.14::x11/gtk+

CONFIGURE_STYLE=gnu
CONFIGURE_ARGS+=--enable-gtk2

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/pixmaps
	${INSTALL_DATA} ${WRKSRC}/xpms/xcdricon.xpm \
		${PREFIX}/share/pixmaps/xcdricon.xpm

.include <bsd.port.mk>
