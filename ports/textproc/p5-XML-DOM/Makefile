# $OpenBSD: Makefile,v 1.11 2003/11/15 15:12:54 sturm Exp $

COMMENT=			perl module to build DOM Level 1 structures

DISTNAME=	XML-DOM-1.42
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	textproc perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=XML/}


BUILD_DEPENDS=  :p5-XML-Parser->=2.30:textproc/p5-XML-Parser	\
		:p5-Libxml-*:textproc/p5-Libxml		\
		:p5-XML-RegExp-*:textproc/p5-XML-RegExp	\
		:p5-libwww-*:www/p5-libwww
RUN_DEPENDS=    ${BUILD_DEPENDS}

# GPL/Artistic
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= perl

.include <bsd.port.mk>
