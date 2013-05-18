# $MirOS: ports/net/GeoIP/Makefile,v 1.1.7.1 2005/03/18 15:47:59 tg Exp $
# $OpenBSD: Makefile,v 1.3 2004/01/30 08:39:49 xsa Exp $

COMMENT=			find the country where IP address/hostname originates from

DISTNAME=	GeoIP-1.2.0
CATEGORIES=	net

HOMEPAGE=	http://www.maxmind.com/geoip/
MASTER_SITES=	http://www.maxmind.com/download/geoip/api/c/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= autoconf no-autoheader
CONFIGURE_ARGS=	--datadir=/var/db \
		${CONFIGURE_SHARED}

EXAMPLESDIR=	${PREFIX}/share/examples/GeoIP

FAKE_FLAGS=	${DESTDIRNAME}=${WRKINST} \
		DEFAULT_CONFIG_FILE=${EXAMPLESDIR}/GeoIP.conf \
		DEFAULT_DB_FILE=${EXAMPLESDIR}/GeoIP.dat

pre-install:
	${INSTALL_DATA_DIR} ${EXAMPLESDIR}

.include <bsd.port.mk>
