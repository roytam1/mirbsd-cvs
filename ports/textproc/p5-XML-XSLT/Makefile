# $OpenBSD: Makefile,v 1.12 2003/11/15 15:12:54 sturm Exp $

COMMENT=			perl module to perform XSLT transformations

DISTNAME=	XML-XSLT-0.32
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	textproc perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=XML/}


BUILD_DEPENDS=  :p5-XML-Parser->=2.23:textproc/p5-XML-Parser \
		:p5-XML-DOM->=1.25:textproc/p5-XML-DOM
RUN_DEPENDS=    ${BUILD_DEPENDS}

# GPL/Artistic
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= perl

.include <bsd.port.mk>
