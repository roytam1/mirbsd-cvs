# $OpenBSD: Makefile,v 1.8 2004/02/25 02:35:16 naddy Exp $

COMMENT=			tool for measuring maximum TCP and UDP bandwidth

DISTNAME=	iperf-1.2
CATEGORIES=    	net

HOMEPAGE=	http://dast.nlanr.net/Projects/Iperf/


PERMIT_PACKAGE_CDROM=	"no fee license"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"no fee license"
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://dast.nlanr.net/Projects/Iperf/

USE_CXX=	Yes
NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/iperf ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/iperf
	${INSTALL_DATA} ${WRKSRC}/doc/* ${PREFIX}/share/doc/iperf

.include <bsd.port.mk>
