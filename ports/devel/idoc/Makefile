# $OpenBSD: Makefile,v 1.2 2004/05/19 06:15:57 dons Exp $

COMMENT=			minimalist documentation tool for Haskell

VSN=			0.2.6
DISTNAME=		idoc-${VSN}
CATEGORIES=		devel
HOMEPAGE=		http://www.cse.unsw.edu.au/~chak/haskell/idoc/
MASTER_SITES=		${HOMEPAGE}

# pure Haskell 98
.if ${MACHINE_ARCH} == "i386" || ${MACHINE_ARCH} == "sparc" || ${MACHINE_ARCH} == "amd64"
MODULES=		lang/ghc
.else
BUILD_DEPENDS+=		bin/nhc98::lang/nhc98
MAKE_FLAGS=		HC=nhc98
.endif

ALL_TARGET=
USE_GMAKE=		Yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/idoc ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/idoc
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/idoc/

do-regress:
	(cd ${WRKSRC}/test && ../idoc Foo.hs && /usr/bin/lynx --dump Foo.html)

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <bsd.port.mk>
