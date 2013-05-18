# $MirOS$
# $OpenBSD: Makefile,v 1.14 2004/01/25 21:10:51 pvalchev Exp $

COMMENT=	NetBus client
VERSION=	0.4
DISTNAME=       linux-netbus-client-v${VERSION}
PKGNAME=	lxnb-${VERSION}-${DASH_VER}
CATEGORIES=	security

PERMIT_PACKAGE_CDROM=	"no obvious license"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"no obvious license"
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	http://ns2.crw.se/~tm/projects/lxnb/
EXTRACT_SUFX=	.tgz

WRKDIST=	${WRKDIR}/lxnb-${VERSION}

pre-build:
	rm -f ${WRKSRC}/lxnetbus

NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/lxnetbus ${PREFIX}/bin/lxnb

.include <bsd.port.mk>
