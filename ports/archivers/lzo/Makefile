# $MirOS: ports/archivers/lzo/Makefile,v 1.6 2007/02/22 22:57:43 tg Exp $
# $OpenBSD: Makefile,v 1.31 2004/02/23 00:33:34 naddy Exp $

COMMENT=		portable speedy lossless data compression library
DISTNAME=		lzo-2.09
CATEGORIES=		archivers devel
MASTER_SITES=		${HOMEPAGE}download/
HOMEPAGE=		http://www.oberhumer.com/opensource/lzo/

# GNU GPLv2+
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static
REGRESS_TARGET=		check test
DOCFILES=		NEWS doc/LZO.FAQ doc/LZO.TXT doc/LZOAPI.TXT

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/lzo
	cd ${WRKSRC} && ${INSTALL_DATA} ${DOCFILES} ${PREFIX}/share/doc/lzo/

.include <bsd.port.mk>
