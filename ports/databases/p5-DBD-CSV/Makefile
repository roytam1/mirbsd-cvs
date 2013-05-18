# $MirOS$
# $OpenBSD: Makefile,v 1.2 2004/01/17 17:23:55 naddy Exp $

COMMENT=		perl DBI driver for CSV files

DISTNAME=		DBD-CSV-0.22
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		databases perl5 

# like Perl
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=DBD/}

B_R_DEPENDS+=		:p5-DBI->=1.08:databases/p5-DBI
B_R_DEPENDS+=		:p5-Text-CSV_XS->0.22:textproc/p5-Text-CSV_XS
B_R_DEPENDS+=		::databases/p5-SQL-Statement

CONFIGURE_STYLE=	perl
PKG_ARCH=		*

.include <bsd.port.mk>
