# $OpenBSD: Makefile,v 1.1.1.1 2004/05/26 13:36:07 sturm Exp $

COMMENT=			update Class::DBI objects through CGI::Untaint

DISTNAME=	Class-DBI-FromCGI-0.94
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	databases perl5 www

# Same as Perl
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=Class/}

CONFIGURE_STYLE=perl

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	::databases/p5-Class-DBI \
		::www/p5-CGI-Untaint

PKG_ARCH=	*

.include <bsd.port.mk>
