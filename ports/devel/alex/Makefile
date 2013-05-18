# $MirOS: ports/devel/alex/Makefile,v 1.3 2008/04/07 19:20:01 tg Exp $
# $OpenBSD: Makefile,v 1.2 2004/04/23 02:17:49 dons Exp $

COMMENT=		lexical analyser generator for Haskell
VSN=			2.0
DISTNAME=		alex-${VSN}
CATEGORIES=		devel
HOMEPAGE=		http://www.haskell.org/alex/

MODULES+=		lang/ghc

MASTER_SITES=		http://www.haskell.org/alex/dist/
MASTER_SITES0=		ftp://ftp.cse.unsw.edu.au/pub/users/dons/alex/
DISTFILES=		${DISTNAME}-src.tar.bz2 alex-regress-${VSN}.tgz:0

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

DOC_DIR=		${PREFIX}/share/doc/alex

post-build:
	cd ${WRKSRC}/alex/doc; ${MAKE_ENV} ${GMAKE} html

post-install:
	${INSTALL_DATA_DIR} ${DOC_DIR}
	cp -R ${WRKSRC}/alex/doc/alex/* ${DOC_DIR}

# BSD style w/o advertising clause
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <bsd.port.mk>
