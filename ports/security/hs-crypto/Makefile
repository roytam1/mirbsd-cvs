# $OpenBSD: Makefile,v 1.1.1.1 2004/05/03 07:36:32 dons Exp $

COMMENT=			Haskell cryptographic library
CATEGORIES=	security

VSN=		1.1.2
DISTNAME=	hs-crypto-${VSN}
MASTER_SITES=	${HOMEPAGE}/downloads/
HOMEPAGE=	http://www.haskell.org/crypto/
DISTFILES=	crypto-${VSN}.tar

MODULES=	lang/ghc
BUILD_DEPENDS+=	::devel/haddock

WRKDIST=	${WRKDIR}/crypto

USE_GMAKE=      Yes
MAKE_ENV+=	"WRKDIST=${WRKDIST}"
ALL_TARGET=

do-regress:
	@(cd ${WRKDIST} ; /bin/sh test.sh)

# 3 different licenses from 3 authors: BSD, GPL, BSD-ish
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <bsd.port.mk>
