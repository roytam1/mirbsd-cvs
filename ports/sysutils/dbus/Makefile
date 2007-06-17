# $MirOS$
# $NetBSD: Makefile,v 1.23 2007/01/17 02:46:59 dmcmahill Exp $
#

COMMENT=		Message bus system
DISTNAME=		dbus-1.0.2
CATEGORIES=		sysutils
MASTER_SITES=		http://dbus.freedesktop.org/releases/dbus/

HOMEPAGE=		http://www.freedesktop.org/Software/dbus

FLAVOR?=
FLAVORS=		no_x11

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
USE_GMAKE=		Yes
MODULES+=		devel/pkgconfig converters/libiconv

CONFIGURE_ARGS+=	--disable-abstract-sockets
CONFIGURE_ARGS+=	--disable-ansi
CONFIGURE_ARGS+=	--disable-asserts
CONFIGURE_ARGS+=	--disable-console-owner-file
CONFIGURE_ARGS+=	--disable-dnotify
CONFIGURE_ARGS+=	--disable-doxygen-docs
CONFIGURE_ARGS+=	--disable-gcov
CONFIGURE_ARGS+=	--disable-selinux
CONFIGURE_ARGS+=	--disable-tests
CONFIGURE_ARGS+=	--disable-verbose-mode
CONFIGURE_ARGS+=	--disable-xml-docs
CONFIGURE_ARGS+=	--enable-checks
CONFIGURE_ARGS+=	--with-xml=expat
CONFIGURE_ARGS+=	--with-dbus-user=_dbus

.if ${FLAVOR:Mno_x11}
CONFIGURE_ARGS+=	--without-x
.else
USE_X11=		Yes
.endif

PKG_SYSCONFSUBDIR=	dbus-1
MAKE_DIRS=		${PKG_SYSCONFDIR}/event.d
MAKE_DIRS+=		${PKG_SYSCONFDIR}/system.d

EGDIR=			${PREFIX}/share/examples/dbus
CONF_FILES=		${EGDIR}/session.conf ${PKG_SYSCONFDIR}/session.conf
CONF_FILES+=		${EGDIR}/system.conf ${PKG_SYSCONFDIR}/system.conf
INSTALLATION_DIRS=	${EGDIR}

RCD_SCRIPTS=		dbus

.include <bsd.port.mk>
