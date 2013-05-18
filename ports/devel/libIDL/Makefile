# $MirOS: ports/devel/libIDL/Makefile,v 1.5 2006/02/09 11:11:22 tg Exp $
# $OpenBSD: Makefile,v 1.15 2004/12/10 20:33:59 marcm Exp $

COMMENT=			IDL parsing library
DISTNAME=		libIDL-0.8.6
CATEGORIES=		devel
HOMEPAGE=		http://www.gnome.org/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/libIDL/0.8/}
EXTRACT_SUFX=		.tar.bz2

LIB_DEPENDS=		glib-2.0.0.0::devel/glib
MODULES=		devel/gettext devel/pkgconfig

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

.include <bsd.port.mk>
