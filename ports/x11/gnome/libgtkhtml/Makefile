# $OpenBSD: Makefile,v 1.5 2003/12/01 04:13:06 marcm Exp $

COMMENT=			lightweight HTML rendering/printing/editing engine

DISTNAME=		libgtkhtml-2.4.1
CATEGORIES=		x11/gnome

HOMEPAGE=		http://www.gnome.org/


# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/libgtkhtml/2.4/}
EXTRACT_SUFX=		.tar.bz2

LIB_DEPENDS=		gailutil.17::x11/gnome/gail
MODULES+=		devel/pkgconfig

USE_GMAKE=		Yes
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--disable-gtk-doc

.include <bsd.port.mk>
