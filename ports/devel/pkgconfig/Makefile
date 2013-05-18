# $MirOS: ports/devel/pkgconfig/Makefile,v 1.6 2007/05/08 22:43:41 tg Exp $
# $OpenBSD: Makefile,v 1.14 2004/02/01 07:20:04 marcm Exp $

COMMENT=		tool for managing library compile/link flags

VERSION=		0.23
DISTNAME=		pkg-config-${VERSION}
PKGNAME=		pkgconfig-${VERSION}-${DASH_VER}
CATEGORIES=		devel
HOMEPAGE=		http://pkg-config.freedesktop.org/
MASTER_SITES=		${HOMEPAGE}releases/ \
			${MASTER_SITE_GNOME:=sources/pkg-config/0.23/}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS+=		glib.1.2::devel/glib1
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ENV+=		GLIB_CFLAGS='-I${LOCALBASE}/include/glib-1.2' \
			GLIB_LIBS='-L${LOCALBASE}/lib -lglib'

.include <bsd.port.mk>
