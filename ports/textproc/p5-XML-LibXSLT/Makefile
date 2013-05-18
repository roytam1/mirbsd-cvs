# $MirOS: ports/textproc/p5-XML-LibXSLT/Makefile,v 1.4 2006/06/03 16:02:41 bsiegert Exp $
# $OpenBSD: Makefile,v 1.20 2004/01/17 15:58:10 naddy Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			fast XSLT module for perl

VERSION=	1.50
DISTNAME=	XML-LibXSLT-${VERSION}
PKGNAME=	p5-${DISTNAME}-1
CATEGORIES=	textproc perl5

HOMEPAGE=	http://www.axkit.org/

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=XML/}


BUILD_DEPENDS=	:p5-XML-LibXML->=0.94:textproc/p5-XML-LibXML
RUN_DEPENDS=	${BUILD_DEPENDS}
LIB_DEPENDS=	xml2.2.6::textproc/libxml \
		xslt.1,exslt.7::textproc/libxslt

# GPL/Artistic
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= perl

.include <bsd.port.mk>
