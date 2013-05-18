# $MirOS: ports/net/rrdtool/Makefile,v 1.7 2008/10/16 19:44:02 tg Exp $
# $OpenBSD: Makefile,v 1.24 2004/02/15 20:59:58 sturm Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}
COMMENT=		system to store and display time-series data
DISTNAME=		rrdtool-1.0.50
CATEGORIES=		net
HOMEPAGE=		http://oss.oetiker.ch/rrdtool/

# GNU GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		http://oss.oetiker.ch/rrdtool/pub/rrdtool-1.0.x/ \
			ftp://ftp.sunet.se/pub/network/monitoring/rrdtool/ \
			http://ftp.sunet.se/pub/network/monitoring/rrdtool/

MODULES+=		graphics/png
MODULES+=		p5
LIB_DEPENDS+=		gd::graphics/gd
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--enable-local-libpng \
			--enable-local-zlib \
			--without-tcllib

post-extract:
	-rm -f ${WRKSRC}/src/getopt.h

post-configure:
	print ',g/define VERSION/d\nwq' | ed -s ${WRKSRC}/config.h

.include <bsd.port.mk>
