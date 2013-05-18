# $MirOS: ports/textproc/p5-XML-LibXML/Makefile,v 1.4 2006/06/03 16:02:41 bsiegert Exp $
# $OpenBSD: Makefile,v 1.18 2004/01/17 15:58:10 naddy Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			perl interface to the libxml2 library

VERSION=	1.54
DISTNAME=	XML-LibXML-${VERSION}
PKGNAME=	p5-${DISTNAME}-1
CATEGORIES=	textproc perl5

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=XML/}


LIB_DEPENDS=	xml2.2.6::textproc/libxml
RUN_DEPENDS=	::textproc/p5-LibXML-Common \
		:p5-XML-SAX-*:textproc/p5-XML-SAX
BUILD_DEPENDS=	${RUN_DEPENDS}

# GPL/Artistic
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= perl

.include <bsd.port.mk>
