# $MirOS: ports/devel/happy/Makefile,v 1.3 2008/04/07 19:20:04 tg Exp $
# $OpenBSD: Makefile,v 1.4 2004/04/23 03:00:07 dons Exp $

COMMENT=		parser generator for the functional language Haskell
VSN=			1.14
DISTNAME=		happy-${VSN}
CATEGORIES=		devel
HOMEPAGE=		http://www.haskell.org/ghc/

MODULES+=		lang/ghc

MASTER_SITES=		http://www.haskell.org/happy/dist/${VSN}/
MASTER_SITES0=		ftp://ftp.cse.unsw.edu.au/pub/users/dons/happy/

DISTFILES=		happy-${VSN}-src.tar.gz     \
			happy-regress-${VSN}.tar.bz2:0

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

DOC_DIR=		${PREFIX}/share/doc/happy

post-build:
	cd ${WRKSRC}/happy/doc; ${MAKE_ENV} ${GMAKE} html

post-install:
	${INSTALL_DATA_DIR} ${DOC_DIR}
	cp -R ${WRKSRC}/happy/doc/happy/* ${DOC_DIR}

# BSD style w/o advertising clause
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <bsd.port.mk>
