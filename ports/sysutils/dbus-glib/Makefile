# $MirOS: ports/sysutils/dbus-glib/Makefile,v 1.1 2007/06/17 18:15:15 bsiegert Exp $
# $NetBSD: Makefile,v 1.12 2007/03/13 11:11:27 drochner Exp $

COMMENT=		glib bindings for the D-BUS message bus system
DISTNAME=		dbus-glib-0.73
CATEGORIES=		sysutils

MASTER_SITES=		http://dbus.freedesktop.org/releases/dbus-glib/
HOMEPAGE=		http://www.freedesktop.org/Software/dbus

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
USE_GMAKE=		Yes
MODULES+=		converters/libiconv
MODULES+=		devel/pkgconfig
MODULES+=		textproc/expat
LIB_DEPENDS+=		dbus-1::sysutils/dbus
LIB_DEPENDS+=		glib-2.0.0.0,gobject-2.0.0.0::devel/glib

CONFIGURE_ARGS+=	--disable-ansi
CONFIGURE_ARGS+=	--disable-asserts
CONFIGURE_ARGS+=	--disable-doxygen-docs
CONFIGURE_ARGS+=	--disable-gcov
CONFIGURE_ARGS+=	--disable-tests
CONFIGURE_ARGS+=	--disable-verbose-mode
CONFIGURE_ARGS+=	--disable-xml-docs
CONFIGURE_ARGS+=	--enable-checks
CONFIGURE_ARGS+=	--with-xml=expat

.include <bsd.port.mk>
