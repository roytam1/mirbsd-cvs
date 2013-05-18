# $MirOS: ports/net/rtorrent/Makefile,v 1.2 2006/03/18 18:26:37 tg Exp $

CATEGORIES=		net
COMMENT=			BitTorrent ncurses client
DISTNAME=		rtorrent-0.4.5
HOMEPAGE=		http://libtorrent.rakshasa.no/
MASTER_SITES=		${HOMEPAGE}downloads/

# GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

DESCR=			${PORTSDIR}/net/libtorrent/pkg/DESCR

MODULES+=		devel/pkgconfig
LIB_DEPENDS+=		torrent:libtorrent->=0.8.5:net/libtorrent
LIB_DEPENDS+=		curl::net/curl

USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-debug \
			--disable-dependency-tracking

SAMPLEDIR=		${PREFIX}/share/examples/rtorrent

post-install:
	${INSTALL_DATA_DIR} ${SAMPLEDIR}
	${INSTALL_DATA} ${WRKSRC}/doc/rtorrent.rc ${SAMPLEDIR}/

.include <bsd.port.mk>
