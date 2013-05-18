# $MirOS: ports/security/vpnc/Makefile,v 1.2 2006/01/01 03:08:26 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/05/14 13:34:51 sturm Exp $

COMMENT=			client for Cisco 3000 VPN concentrators
VERSION=		0.2-rm+zomb.1
DISTNAME=		vpnc-${VERSION}
PKGNAME=		vpnc-${VERSION:C/[-+]/_/g}-0
CATEGORIES=		security net
HOMEPAGE=		http://www.unix-ag.uni-kl.de/~massar/vpnc/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}

LIB_DEPENDS=		gcrypt.12:libgcrypt->=1.2:security/libgcrypt

USE_GMAKE=		Yes
NO_REGRESS=		Yes

ALL_TARGET=		vpnc

do-configure:
	@perl -pi -e "s,/etc,${SYSCONFDIR},g" ${WRKSRC}/{README,vpnc.c,vpnc.8}
	@sed -e "s,%%PREFIX%%,${PREFIX},g" ${FILESDIR}/vpnc.sh > ${WRKBUILD}/vpnc.sh

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/vpnc ${PREFIX}/sbin
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/vpnc
	${INSTALL_DATA} ${WRKBUILD}/README ${PREFIX}/share/doc/vpnc
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/vpnc
	${INSTALL_DATA} ${WRKBUILD}/vpnc.conf ${PREFIX}/share/examples/vpnc
	${INSTALL_DATA} ${WRKBUILD}/vpnc.sh ${PREFIX}/share/examples/vpnc

.include <bsd.port.mk>
