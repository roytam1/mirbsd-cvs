# $OpenBSD: Makefile,v 1.14 2003/11/15 15:12:54 sturm Exp $

COMMENT=			modules for parsing and evaluating XPath statements

DISTNAME=	XML-XPath-1.13
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	textproc perl5

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=XML/}

BUILD_DEPENDS=  :p5-XML-Parser->=2.23:textproc/p5-XML-Parser
RUN_DEPENDS=    ${BUILD_DEPENDS}

# GPL/Artistic
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= perl

DOCDIR=	${PREFIX}/share/examples/p5-XML-XPath
SRCDOCDIR= ${WRKSRC}/examples

post-install:
	${INSTALL_DATA_DIR} ${DOCDIR}
	${INSTALL_SCRIPT} ${SRCDOCDIR}/xpath ${DOCDIR}/
	${INSTALL_DATA} ${SRCDOCDIR}/*.xml ${DOCDIR}/

.include <bsd.port.mk>
