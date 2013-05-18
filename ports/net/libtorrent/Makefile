# $MirOS: ports/net/libtorrent/Makefile,v 1.3 2006/09/14 00:11:52 tg Exp $

CATEGORIES=		net
COMMENT=		BitTorrent client back-end library
DISTNAME=		libtorrent-0.10.3
HOMEPAGE=		http://libtorrent.rakshasa.no/
MASTER_SITES=		${HOMEPAGE}downloads/

# GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MODULES+=		devel/pkgconfig
#LIB_DEPENDS+=		sigc-2?0::devel/libsigc++
# ports/infrastructure/scripts/resolve-lib sucks major arse
LIB_DEPENDS+=		sigc-2.0.0.0::devel/libsigc++

USE_CXX=		Yes
CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--disable-debug \
			--disable-dependency-tracking \
			--disable-libtool-lock \
			--enable-ipv6 \
			--with-openssl=/usr

.include <bsd.port.mk>
