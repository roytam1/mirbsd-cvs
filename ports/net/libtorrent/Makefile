# $MirOS: ports/net/libtorrent/Makefile,v 1.2 2006/03/18 18:14:58 tg Exp $

CATEGORIES=		net
COMMENT=			BitTorrent client back-end library
DISTNAME=		libtorrent-0.8.5
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
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--with-openssl=/usr \
			--disable-libtool-lock \
			--disable-dependency-tracking

.include <bsd.port.mk>
