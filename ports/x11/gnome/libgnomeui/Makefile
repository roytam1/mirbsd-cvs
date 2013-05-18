# $MirOS: ports/x11/gnome/libgnomeui/Makefile,v 1.3 2006/02/09 09:36:23 tg Exp $
# $OpenBSD: Makefile,v 1.8 2004/12/15 13:57:56 alek Exp $

COMMENT=			user interface components for GNOME

DISTNAME=		libgnomeui-2.12.0
CATEGORIES=		x11/gnome

HOMEPAGE=		http://www.gnome.org/


# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/libgnomeui/2.12/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS=		:gnome-common-*:x11/gnome/common
LIB_DEPENDS=		bonoboui-2::x11/gnome/libbonoboui \
			gnome-keyring::x11/gnome/keyring

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--disable-gtk-doc

.include <bsd.port.mk>
