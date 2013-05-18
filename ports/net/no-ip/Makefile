# $MirOS$
# $OpenBSD: Makefile,v 1.7 2004/01/13 14:46:11 wilfried Exp $

COMMENT=		No-IP.com Dynamic DNS client
VSN=			2.1.1
DISTNAME=		noip-${VSN}
PKGNAME=		no-ip-${VSN}-${DASH_VER}
CATEGORIES=		net
HOMEPAGE=		http://www.no-ip.com/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}client/linux/ \
			${MASTER_SITE_FINK}

NO_REGRESS=		Yes

ALL_TARGET=		noip2

do-configure:
	@perl -pi -e 's|_SYSCONFDIR_|${SYSCONFDIR}|g' ${WRKSRC}/noip2.c

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/noip2 ${PREFIX}/sbin
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/no-ip/
	${INSTALL_DATA} ${WRKSRC}/README.FIRST ${PREFIX}/share/doc/no-ip/

.include <bsd.port.mk>
