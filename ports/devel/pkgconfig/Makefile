# $MirOS: ports/devel/pkgconfig/Makefile,v 1.3 2006/09/14 00:08:49 tg Exp $
# $OpenBSD: Makefile,v 1.14 2004/02/01 07:20:04 marcm Exp $

COMMENT=		tool for managing library compile/link flags
DISTNAME=		pkgconfig-0.15.0
PKGNAME=		${DISTNAME}-1
CATEGORIES=		devel
HOMEPAGE=		http://www.freedesktop.org/software/pkgconfig/
MASTER_SITES=		${HOMEPAGE}releases/ \
			${MASTER_SITE_GNOME:=sources/pkgconfig/0.15/}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS+=		glib.1.2::devel/glib1
CONFIGURE_STYLE=	autoconf
CONFIGURE_ENV+=		GLIB_CFLAGS='-I${LOCALBASE}/include/glib-1.2' \
			GLIB_LIBS='-L${LOCALBASE}/lib -lglib'
CONFIGURE_ARGS+=	--disable-libtool-lock

.include <bsd.port.mk>
