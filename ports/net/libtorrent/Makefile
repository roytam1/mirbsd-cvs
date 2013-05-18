# $MirOS: ports/net/libtorrent/Makefile,v 1.5 2007/02/22 22:57:54 tg Exp $

CATEGORIES=		net
COMMENT=		BitTorrent client back-end library
DISTNAME=		libtorrent-0.11.4
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
			--with-openssl=/usr

# not for now: upstream says it's broken in the app itself
#			--enable-ipv6 \

.include <mirports.sys.mk>

.if ${OStype:M*BSD}
CONFIGURE_ARGS+=	--with-kqueue
.endif

.include <bsd.port.mk>
