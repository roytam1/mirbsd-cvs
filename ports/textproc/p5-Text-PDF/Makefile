# $OpenBSD: Makefile,v 1.16 2003/11/15 15:12:54 sturm Exp $

COMMENT=			perl modules for creating and manipulating PDF

DISTNAME=	Text-PDF-0.25
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	textproc perl5


# Artistic
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=Text/}

BUILD_DEPENDS=	:p5-Compress-Zlib-*:archivers/p5-Compress-Zlib
RUN_DEPENDS=	${BUILD_DEPENDS}

CONFIGURE_STYLE= perl

EXAMPLE_DIR=	${PREFIX}/share/examples/p5-Text-PDF
EXAMPLE_LOC=	${WRKSRC}/examples

post-install:
	${INSTALL_DATA_DIR} ${EXAMPLE_DIR}
	${INSTALL_SCRIPT} ${EXAMPLE_LOC}/*.pl ${EXAMPLE_DIR}/
	${INSTALL_DATA} ${EXAMPLE_LOC}/*.CFG ${EXAMPLE_DIR}/
	${INSTALL_DATA} ${EXAMPLE_LOC}/*.pdf ${EXAMPLE_DIR}/

.include <bsd.port.mk>
