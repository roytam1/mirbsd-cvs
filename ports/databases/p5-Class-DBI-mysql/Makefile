# $OpenBSD: Makefile,v 1.1.1.1 2004/05/26 13:36:08 sturm Exp $

COMMENT=			extensions to Class::DBI for MySQL

DISTNAME=	Class-DBI-mysql-0.22
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	databases perl5


# Same as Perl
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=Class/}

CONFIGURE_STYLE=perl

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	::databases/p5-Class-DBI \
		::databases/p5-DBD-mysql
REGRESS_DEPENDS=:mysql-server-4.*:databases/mysql,-server

PKG_ARCH=	*

pre-regress:
	@mysqladmin ping >/dev/null 2>&1 || (echo 'mysql needs to be running'; exit 1)
	-@mysqladmin create test >/dev/null 2>&1

.include <bsd.port.mk>
