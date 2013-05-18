# $OpenBSD: Makefile,v 1.3 2004/05/07 23:35:51 pvalchev Exp $

BROKEN=			unfetchable distfile

COMMENT=		clustering algorithm for graphs
VSN=		04-105
DISTNAME=	mcl-${VSN}
PKGNAME=	mcl-${VSN:S,-,.,}-${DASH_VER}
CATEGORIES=	math

HOMEPAGE=	http://micans.org/mcl/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${HOMEPAGE}src/

CONFIGURE_STYLE=gnu

.include <bsd.port.mk>
