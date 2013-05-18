# $MirOS: ports/net/openvpn/Makefile,v 1.15 2008/03/09 17:23:19 tg Exp $
# $OpenBSD: Makefile,v 1.2 2003/12/30 21:29:53 sturm Exp $

COMMENT=		easy-to-use, robust, highly configurable VPN solution
VERSION=		2.0.9
DASH_VER=		1
DISTNAME=		openvpn-${VERSION}
PKGNAME=		openvpn-${VERSION:S/_//}-${DASH_VER}
CATEGORIES=		net security
HOMEPAGE=		http://openvpn.net/
MASTER_SITES=		${HOMEPAGE}release/

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVOURS=		no_lzo static
FLAVOUR?=

.if !${FLAVOUR:L:Mno_lzo}
.  if !${FLAVOUR:L:Mstatic}
LIB_DEPENDS+=		lzo2::archivers/lzo
RUN_DEPENDS+=		:lzo->=2.*:archivers/lzo
.  endif
BUILD_DEPENDS+=		:lzo->=2.*:archivers/lzo
.endif

.if ${FLAVOUR:L:Mstatic}
LDSTATIC=		-static
.endif

USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
.if ${FLAVOUR:L:Mno_lzo}
CONFIGURE_ARGS+=	--disable-lzo
.else
CONFIGURE_ARGS+=	--with-lzo-headers=${LOCALBASE}/include \
			--with-lzo-lib=${LOCALBASE}/lib
.endif

SAMPLES_DIR=		${PREFIX}/share/examples/openvpn

post-build:
	for a in ${WRKSRC}/easy-rsa/{,2.0/}[!2W]*; do print \
	    '%g#/bin/bash#s##${SHELL}#g\nwq' | ed -s $$a; done

post-install:
	${INSTALL_DATA_DIR} ${SAMPLES_DIR}
	${INSTALL_DATA_DIR} ${SAMPLES_DIR}/easy-rsa/2.0
	${INSTALL_DATA_DIR} ${SAMPLES_DIR}/sample-config-files
	${INSTALL_DATA_DIR} ${SAMPLES_DIR}/sample-keys
	${INSTALL_DATA_DIR} ${SAMPLES_DIR}/sample-scripts
	${INSTALL_DATA} ${WRKSRC}/easy-rsa/[!2W]* \
	    ${SAMPLES_DIR}/easy-rsa/
	${INSTALL_DATA} ${WRKSRC}/easy-rsa/2.0/* \
	    ${SAMPLES_DIR}/easy-rsa/2.0/
	${INSTALL_DATA} ${WRKSRC}/sample-config-files/* \
	    ${SAMPLES_DIR}/sample-config-files/
	${INSTALL_DATA} ${WRKSRC}/sample-keys/* \
	    ${SAMPLES_DIR}/sample-keys/
	${INSTALL_DATA} ${WRKSRC}/sample-scripts/* \
	    ${SAMPLES_DIR}/sample-scripts/

.include <bsd.port.mk>
