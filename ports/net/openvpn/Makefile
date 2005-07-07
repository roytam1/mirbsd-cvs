# $MirOS$
# $OpenBSD: Makefile,v 1.2 2003/12/30 21:29:53 sturm Exp $

COMMENT=	"easy-to-use, robust, and highly configurable VPN"
VERSION=	2.0_rc6
DISTNAME=	openvpn-${VERSION}
PKGNAME=	openvpn-${VERSION:S/_//}-0
CATEGORIES=	net security
HOMEPAGE=	http://openvpn.net/
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=openvpn/}
#MASTER_SITES=	${HOMEPAGE}beta/

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=	lzo::archivers/lzo

SEPARATE_BUILD=	concurrent
USE_GMAKE=	Yes
CONFIGURE_STYLE=autoconf
AUTOCONF_NEW=	Yes
CONFIGURE_ARGS+=--with-lzo-headers=${LOCALBASE}/include \
		--with-lzo-lib=${LOCALBASE}/lib
FAKE_FLAGS+=	mkdir_p='/bin/mkdir -p'

SAMPLES_DIR=	${PREFIX}/share/examples/openvpn

post-build:
	for a in ${WRKSRC}/easy-rsa/[!W]*; do print \
	    'g,/bin/bash,s,,/bin/ksh,g\nwq' | ed -s $$a; done

post-install:
	${INSTALL_DATA_DIR} ${SAMPLES_DIR}
	${INSTALL_DATA_DIR} ${SAMPLES_DIR}/easy-rsa
	${INSTALL_DATA_DIR} ${SAMPLES_DIR}/sample-config-files
	${INSTALL_DATA_DIR} ${SAMPLES_DIR}/sample-keys
	${INSTALL_DATA_DIR} ${SAMPLES_DIR}/sample-scripts
	${INSTALL_DATA} ${WRKSRC}/easy-rsa/[!W]* ${SAMPLES_DIR}/easy-rsa/
	${INSTALL_DATA} ${WRKSRC}/sample-config-files/* ${SAMPLES_DIR}/sample-config-files/
	${INSTALL_DATA} ${WRKSRC}/sample-keys/* ${SAMPLES_DIR}/sample-keys/
	${INSTALL_DATA} ${WRKSRC}/sample-scripts/* ${SAMPLES_DIR}/sample-scripts/

.include <bsd.port.mk>
