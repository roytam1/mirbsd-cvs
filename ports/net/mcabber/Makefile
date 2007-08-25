# $MirOS$

COMMENT=		curses-based jabber client implementation
DISTNAME=		mcabber-0.9.3
CATEGORIES=		net
EXTRACT_SUFX=		.tar.bz2
HOMEPAGE=		http://www.lilotux.net/~mikael/mcabber/
MASTER_SITES=		${HOMEPAGE}files/
RESPONSIBLE=		Jonathan “ciruZ” Schleifer <js@webkeks.org>

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

USE_GMAKE=		Yes
USE_CXX=		Yes

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--enable-gpgme \
			--disable-aspell \
			--with-ssl \
			--disable-hgcset \
			--disable-nls

LIB_DEPENDS+=		glib-2.0.0.800,gmodule-2.0.0.800,gobject-2.0.0.800::devel/glib \
			gpgme::security/gpgme

.include <bsd.port.mk>
