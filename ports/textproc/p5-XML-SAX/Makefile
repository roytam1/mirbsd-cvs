# $MirOS: ports/textproc/p5-XML-SAX/Makefile,v 1.4 2009/01/01 17:34:56 bsiegert Exp $
# $OpenBSD: Makefile,v 1.9 2003/11/15 15:12:54 sturm Exp $

COMMENT=	perl interface to the SAX2 XML Parser

VERSION=	0.96
DASH_VER=	1
DISTNAME=	XML-SAX-${VERSION}
PKGNAME=	p5-${DISTNAME}-${DASH_VER}
CATEGORIES=	textproc perl5

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=XML/}

# GPL/Artistic
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

B_R_DEPENDS=	:p5-XML-NamespaceSupport->=0.03:textproc/p5-XML-NamespaceSupport

CONFIGURE_STYLE= perl

# Install parser template
post-install:
	@${INSTALL_DATA} ${FILESDIR}/ParserDetails.ini	\
		${PREFIX}/libdata/perl5/site_perl/XML/SAX/

.include <bsd.port.mk>
