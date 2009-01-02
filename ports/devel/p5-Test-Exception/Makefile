# $MirOS: ports/infrastructure/templates/perlmod.Makefile,v 1.1 2009/01/01 17:11:33 bsiegert Exp $

COMMENT=		test exception based code
DISTNAME=		Test-Exception-0.27
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		devel perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=../../authors/id/A/AD/ADIE}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	perl

B_R_DEPENDS+=		:p5-Sub-Uplevel>=0.18:devel/p5-Sub-Uplevel

PKG_ARCH=		*

.include <bsd.port.mk>
