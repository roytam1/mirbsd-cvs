# $OpenBSD: Makefile,v 1.18 2003/06/29 04:48:38 avsm Exp $

COMMENT=			Lucent remote access RADIUS server

DISTNAME=	radius21
PKGNAME=	radiusd-lucent-2.1-6
CATEGORIES=	net
MASTER_SITES=	http://www.vergenet.net/linux/radius/download/
PATCHFILES=	radius-2.1.comprehensive.6.patch.gz
EXTRACT_SUFX=	.tar.Z

HOMEPAGE=	http://www.vergenet.net/linux/radius/


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

WRKDIST=	${WRKDIR}
WRKSRC=		${WRKDIST}/radius/src
CPPFLAGS+=	-DNOSHADOW -DNDBM
NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/builddbm ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKSRC}/dbmkeys ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKSRC}/dbmrec ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKSRC}/md5test ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKSRC}/radtest ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKSRC}/testuser ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKSRC}/radiusd ${PREFIX}/sbin
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/radiusd-lucent
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/radiusd-lucent/menus
	${INSTALL_DATA} ${WRKDIST}/radius/raddb/clients \
		${PREFIX}/share/examples/radiusd-lucent/
	${INSTALL_DATA} ${WRKDIST}/radius/raddb/config.aeg.example \
		${PREFIX}/share/examples/radiusd-lucent/
	${INSTALL_DATA} ${WRKDIST}/radius/raddb/dictionary \
		${PREFIX}/share/examples/radiusd-lucent/
	${INSTALL_DATA} ${WRKDIST}/radius/raddb/proxy \
		${PREFIX}/share/examples/radiusd-lucent/
	${INSTALL_DATA} ${WRKDIST}/radius/raddb/users \
		${PREFIX}/share/examples/radiusd-lucent/
	${INSTALL_DATA} ${WRKDIST}/radius/raddb/menus/menu1 \
		${PREFIX}/share/examples/radiusd-lucent/menus/
	${INSTALL_DATA} ${WRKDIST}/radius/raddb/menus/menu2 \
		${PREFIX}/share/examples/radiusd-lucent/menus/
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/radiusd-lucent
	${INSTALL_DATA} ${WRKDIST}/radius/LICENSE \
		${PREFIX}/share/doc/radiusd-lucent/
	${INSTALL_DATA} ${WRKDIST}/radius/README \
		${PREFIX}/share/doc/radiusd-lucent/
	${INSTALL_DATA} ${WRKDIST}/radius/README.patched \
		${PREFIX}/share/doc/radiusd-lucent/

.include <bsd.port.mk>
