# $MirOS: ports/infrastructure/templates/perlmod.Makefile,v 1.1 2009/01/01 17:11:33 bsiegert Exp $

COMMENT=		extremely flexible deep comparison
DISTNAME=		Test-Deep-0.103
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		devel perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=../../authors/id/F/FD/FDALY}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	perl

B_R_DEPENDS+=		:p5-Test-Tester>=0.04:devel/p5-Test-Tester
B_R_DEPENDS+=		:p5-Test-NoWarnings>=0.02:devel/p5-Test-NoWarnings
B_R_DEPENDS+=		:p5-Scalar-List-Utils>=1.09:devel/p5-Scalar-List-Utils

PKG_ARCH=		*

.include <bsd.port.mk>
