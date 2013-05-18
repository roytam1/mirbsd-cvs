# $OpenBSD: Makefile,v 1.1.1.1 2004/05/09 10:30:22 dons Exp $
# $FreeBSD: ports/devel/hs-hpl/Makefile,v 1.11 2004/03/11 07:48:11 obraun Exp $

# only for archs to which the GHC ffi has been ported
ONLY_FOR_PLATFORM=	*:*:i386 *:*:sparc

COMMENT=			Haskell library for concurrent and distributed programming

VSN=		0.4.1
DISTNAME=	hs-ports-${VSN}
CATEGORIES=	devel
HOMEPAGE=	http://www.cse.unsw.edu.au/~chak/haskell/ports/ 
MASTER_SITES=	${HOMEPAGE}
DISTFILES=	ports-${VSN}.tar.gz

MODULES=	lang/ghc

WRKDIST=	${WRKDIR}/ports-${VSN}
USE_GMAKE=	Yes
CONFIGURE_STYLE=gnu
CONFIGURE_ARGS+=--prefix=${PREFIX}

do-regress:
	@( cd ${WRKDIST}/tests && sh test.sh )

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <bsd.port.mk>
