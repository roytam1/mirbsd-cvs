# $MirOS: ports/infrastructure/templates/perlmod.Makefile,v 1.2 2009/01/04 17:20:07 bsiegert Exp $

COMMENT=		time zone object base class and factory
DISTNAME=		DateTime-TimeZone-0.8301
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		converters perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=../../authors/id/D/DR/DROLSKY/}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	perl modbuild

B_R_DEPENDS+=		:p5-PathTools>=3:devel/p5-PathTools
B_R_DEPENDS+=		:p5-Class-Singleton>=1.03:devel/p5-Class-Singleton
B_R_DEPENDS+=		:p5-Params-Validate>=0.72:devel/p5-Params-Validate

PKG_ARCH=		*

.include <bsd.port.mk>
