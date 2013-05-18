# $MirOS: ports/devel/haddock/Makefile,v 1.3 2008/04/07 19:20:03 tg Exp $
# $OpenBSD: Makefile,v 1.4 2004/04/23 02:40:16 dons Exp $

COMMENT=		documentation tool for the functional language Haskell
VSN=			0.6
DISTNAME=		haddock-${VSN}
CATEGORIES=		devel
HOMEPAGE=		http://www.haskell.org/haddock/

MODULES+=		lang/ghc

MASTER_SITES=		http://www.haskell.org/haddock/
MASTER_SITES0=		ftp://ftp.cse.unsw.edu.au/pub/users/dons/haddock/

DISTFILES=		${DISTNAME}-src.tar.gz \
			haddock-regress-${VSN}.tgz:0

BUILD_DEPENDS+=		::textproc/docbook \
			::textproc/docbook-dsssl \
			::textproc/sgmlformat \
			::textproc/openjade \
			::textproc/iso8879 \
			::textproc/linuxdoc \
			::textproc/html \
			::print/jadetex

MODULES+=		textproc/expat

USE_GMAKE=		Yes
USE_CXX=		Yes
CONFIGURE_STYLE=	gnu dest
CONFIGURE_ENV=		SGML_CATALOG_FILES=${LOCALBASE}/share/sgml/catalog
MAKE_ENV=		SGML_CATALOG_FILES=${LOCALBASE}/share/sgml/catalog

DOC_DIR=	${PREFIX}/share/doc/haddock

post-build:
	cd ${WRKSRC}/haddock/doc; ${MAKE_ENV} ${GMAKE} html

post-install:
	${INSTALL_DATA_DIR} ${DOC_DIR}
	cp -R ${WRKSRC}/haddock/doc/haddock/* ${DOC_DIR}

# BSD style w/o advertising clause
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

.include <bsd.port.mk>
