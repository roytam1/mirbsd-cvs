# $MirOS: ports/infrastructure/templates/perlmod.Makefile,v 1.2 2009/01/04 17:20:07 bsiegert Exp $

COMMENT=		localization support for DateTime.pm
DISTNAME=		DateTime-Locale-0.42
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		converters perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=../../authors/id/D/DR/DROLSKY/}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	perl

B_R_DEPENDS+=		::devel/p5-List-MoreUtils
B_R_DEPENDS+=		::devel/p5-Class-ISA
B_R_DEPENDS+=		::devel/p5-Params-Validate
B_R_DEPENDS+=		::devel/p5-Module-Build

PKG_ARCH=		*

.include <bsd.port.mk>
