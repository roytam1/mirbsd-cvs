# $MirOS: ports/net/centericq/Makefile,v 1.1.7.1 2005/03/18 15:48:03 tg Exp $
# $OpenBSD: Makefile,v 1.24 2004/02/03 08:37:55 brad Exp $

COMMENT=		"curses-based multiprotocol IM client implementation"
DISTNAME=		centericq-4.20.0
CATEGORIES=		net
MASTER_SITES=		http://konst.org.ua/download/ \
			http://konst.home.welcomehome.org/ \
			http://centericq.de/archive/source/releases/
HOMEPAGE=		http://konst.org.ua/en/centericq
RESPONSIBLE=		Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>

# GNU GPLv2
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

LIB_DEPENDS+=		curl.2::net/curl
USE_GMAKE=		Yes
USE_CXX=		Yes

CONFIGURE_STYLE=	autoconf no-autoheader
CONFIGURE_ARGS+=	--with-openssl \
			--without-gpgme \
			--without-libjpeg \
			--disable-msn \
			--disable-nls

MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/connwrap-0.1 \
			${WRKSRC}/firetalk-0.1 ${WRKSRC}/kkconsui-0.1 \
			${WRKSRC}/kkstrtext-0.1 ${WRKSRC}/kksystr-0.1 \
			${WRKSRC}/libgadu-0.1 ${WRKSRC}/libicq2000-0.1 \
			${WRKSRC}/libjabber-0.1 ${WRKSRC}/libmsn-0.1 \
			${WRKSRC}/libyahoo2-0.1

DOCS=			ChangeLog FAQ README

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/centericq
	cd ${WRKSRC} && ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/doc/centericq/
	${INSTALL_DATA} ${WRKSRC}/centericq.1 ${PREFIX}/man/man1/

.include <bsd.port.mk>
