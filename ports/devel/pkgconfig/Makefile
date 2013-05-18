# $MirOS: ports/devel/pkgconfig/Makefile,v 1.7 2008/12/26 15:42:05 tg Exp $
# $OpenBSD: Makefile,v 1.14 2004/02/01 07:20:04 marcm Exp $

COMMENT=		tool for managing library compile/link flags
VERSION=		0.23
DASH_VER=		0
DISTNAME=		pkg-config-${VERSION}
PKGNAME=		pkgconfig-${VERSION}-${DASH_VER}
CATEGORIES=		devel
HOMEPAGE=		http://pkgconfig.freedesktop.org/
MASTER_SITES=		${HOMEPAGE}releases/ \
			${MASTER_SITE_GNOME:=sources/pkgconfig/0.23/}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS+=		glib.1.2::devel/glib1
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--with-pc-path=/usr/libdata/pkgconfig
CONFIGURE_ENV+=		GLIB_CFLAGS=${GLIB_CFLAGS:Q} \
			GLIB_LIBS=${GLIB_LIBS:Q}
GLIB_CFLAGS=		-I${LOCALBASE:Q}/include/glib-1.2
GLIB_LIBS=		-L${LOCALBASE:Q}/lib -lglib

.include <bsd.port.mk>
