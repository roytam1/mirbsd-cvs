# $OpenBSD: Makefile,v 1.1.1.1 2004/05/26 13:36:07 sturm Exp $

COMMENT=			determine type information for columns

DISTNAME=	Class-DBI-Plugin-Type-0.02
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	databases perl5


# Same as Perl
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=Class/}

CONFIGURE_STYLE=perl

RUN_DEPENDS=	::databases/p5-Class-DBI

PKG_ARCH=	*

.include <bsd.port.mk>
