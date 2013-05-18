# $OpenBSD: Makefile,v 1.4 2004/04/18 20:43:48 wilfried Exp $

BROKEN=			depends on mysql, which is broken

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			MySQL drivers for the Perl DBI

DISTNAME=		DBD-mysql-2.9003
PKGNAME=		p5-${DISTNAME}-0
CATEGORIES=		databases perl5


# artistic
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=DBD/}

BUILD_DEPENDS=		:p5-DBI->=1.08:databases/p5-DBI
RUN_DEPENDS=		:p5-DBI->=1.08:databases/p5-DBI
LIB_DEPENDS=		lib/mysql/mysqlclient.10::databases/mysql
REGRESS_DEPENDS=	:mysql-server-4.*:databases/mysql,-server

CONFIGURE_STYLE=	perl

pre-regress:
	@mysqladmin ping >/dev/null 2>&1 || (echo 'mysql needs to be running'; exit 1)
	-@mysqladmin create test >/dev/null 2>&1

.include <bsd.port.mk>
