# $MirOS: ports/x11/gnome/libbonoboui/Makefile,v 1.2 2005/12/29 18:15:41 bsiegert Exp $
# $OpenBSD: Makefile,v 1.12 2004/12/15 13:57:56 alek Exp $

COMMENT=			user interface components for bonobo

DISTNAME=		libbonoboui-2.10.1
CATEGORIES=		x11/gnome

HOMEPAGE=		http://www.gnome.org/


# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/libbonoboui/2.10/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS=		:p5-XML-Parser-*:textproc/p5-XML-Parser
LIB_DEPENDS=		gnome-2::x11/gnome/libgnome \
			gnomecanvas-2::x11/gnome/libgnomecanvas \
			popt.0.3::devel/popt

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--disable-gtk-doc

.include <bsd.port.mk>
