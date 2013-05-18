# $MirOS: ports/devel/atk/Makefile,v 1.4 2006/02/09 11:11:17 tg Exp $
# $OpenBSD: Makefile,v 1.10 2004/12/10 20:33:59 marcm Exp $

COMMENT=			accessibility toolkit used by gtk+
DISTNAME=		atk-1.10.1
CATEGORIES=		devel
HOMEPAGE=		http://www.gtk.org

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/atk/1.10/}
EXTRACT_SUFX=           .tar.bz2

MODULES=		devel/gettext devel/pkgconfig
LIB_DEPENDS=		glib-2.0.0.800,gmodule-2.0.0.800,gobject-2.0.0.800::devel/glib

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static

.include <bsd.port.mk>
