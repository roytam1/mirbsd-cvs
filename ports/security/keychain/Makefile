# $OpenBSD: Makefile,v 1.9 2004/05/15 12:55:06 sturm Exp $

BROKEN=			unfetchable distfiles

COMMENT=		front-end to ssh-agent

DISTNAME=		keychain-2.3.0
CATEGORIES=		security

HOMEPAGE=		http://www.gentoo.org/proj/en/keychain.xml


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://www.ibiblio.org/pub/Linux/distributions/gentoo/distfiles/
EXTRACT_SUFX=		.tar.bz2

NO_BUILD=		Yes
NO_REGRESS=		Yes
PKG_ARCH=		*

do-install:
	${INSTALL_SCRIPT} ${WRKDIST}/keychain ${PREFIX}/bin
	${INSTALL_DATA} ${WRKDIST}/keychain.1 ${PREFIX}/man/man1

.include <bsd.port.mk>
