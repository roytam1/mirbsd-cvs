# $MirOS: ports/devel/c2hs/Makefile,v 1.3 2009/04/18 19:53:26 bsiegert Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/05/08 07:21:03 dons Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 OpenBSD:*:sparc OpenBSD:*:amd64

COMMENT=		interface generator for Haskell to C bindings

VSN=			0.12.0
DISTNAME=		c2hs-${VSN}
CATEGORIES=		devel
HOMEPAGE=		http://www.cse.unsw.edu.au/~chak/haskell/c2hs/
MASTER_SITES=		${HOMEPAGE}

MODULES=		lang/ghc

USE_GMAKE=		Yes
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--prefix=${PREFIX}

post-build:
	@(cd ${WRKSRC}/doc/c2hs && ${MAKE_PROGRAM} man1/c2hs-config.1 man1/c2hs.1)

post-install:
	@(cd ${WRKSRC}/doc/c2hs/man1 && \
		${INSTALL_MAN} c2hs-config.1 c2hs.1 ${PREFIX}/man/man1)

do-regress:
	@(cd ${WRKDIST}/c2hs/tests && ${MAKE_PROGRAM})

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <bsd.port.mk>
