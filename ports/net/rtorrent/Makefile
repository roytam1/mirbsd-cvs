# $MirOS: ports/net/rtorrent/Makefile,v 1.3 2006/09/14 00:12:15 tg Exp $

CATEGORIES=		net
COMMENT=		BitTorrent ncurses client
DISTNAME=		rtorrent-0.6.3
HOMEPAGE=		http://libtorrent.rakshasa.no/
MASTER_SITES=		${HOMEPAGE}downloads/

# GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

DESCR=			${PORTSDIR}/net/libtorrent/pkg/DESCR

MODULES+=		devel/pkgconfig
LIB_DEPENDS+=		torrent:libtorrent->=0.10.3:net/libtorrent
LIB_DEPENDS+=		curl:curl->=7.12.0:net/curl

USE_CXX=		Yes
CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	--disable-debug \
			--enable-ipv6 \
			--disable-libtool-lock \
			--disable-dependency-tracking

SAMPLEDIR=		${PREFIX}/share/examples/rtorrent

post-install:
	${INSTALL_DATA_DIR} ${SAMPLEDIR}
	${INSTALL_DATA} ${WRKSRC}/doc/rtorrent.rc ${SAMPLEDIR}/

.include <bsd.port.mk>
