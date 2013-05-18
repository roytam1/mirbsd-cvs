# $MirOS: ports/devel/glib/Makefile,v 1.20 2009/08/05 07:54:08 tg Exp $
# $OpenBSD: Makefile,v 1.19 2004/12/22 06:31:05 espie Exp $

COMMENT=		general-purpose utility library
COMMENT-docs=		glib2 documentation
VERSION=		2.16.6
DASH_VER=		0
DISTNAME=		glib-${VERSION}
PKGNAME=		glib2-${VERSION}-${DASH_VER}
PKGNAME-docs=		glib2-docs-${VERSION}-${DASH_VER}
CATEGORIES=		devel
HOMEPAGE=		http://www.gtk.org

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES+=           ${MASTER_SITE_GNOME:=sources/glib/${VERSION:R}/}
MASTER_SITES+=		ftp://ftp.gtk.org/pub/glib/${VERSION:R}/
EXTRACT_SUFX=		.tar.bz2

MULTI_PACKAGES=		-docs
SUBPACKAGE?=

.if defined(PACKAGING) && ${SUBPACKAGE} == "-docs"
PKG_ARCH=		*
.else
MODULES=		devel/gettext devel/pkgconfig converters/libiconv
.endif

# hppa's threads are broken (configure test gives Bus error)...
.if (${MACHINE_ARCH} == "hppa")
CONFIGURE_ARGS+=	--disable-threads
.else
CONFIGURE_ARGS+=	--with-threads=posix
.endif
CONFIGURE_ARGS+=	--disable-rebuilds

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static

.include <bsd.port.mk>
