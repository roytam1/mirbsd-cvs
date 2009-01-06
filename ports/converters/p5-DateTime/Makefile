# $MirOS: ports/infrastructure/templates/perlmod.Makefile,v 1.2 2009/01/04 17:20:07 bsiegert Exp $

COMMENT=		date and time object
DISTNAME=		DateTime-0.4501
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		converters perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=../../authors/id/D/DR/DROLSKY/}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	perl

B_R_DEPENDS+=		:p5-DateTime-TimeZone>=0.59:converters/p5-DateTime-TimeZone
B_R_DEPENDS+=		:p5-Params-Validate>=0.76:devel/p5-Params-Validate
B_R_DEPENDS+=		::devel/p5-Scalar-List-Utils
B_R_DEPENDS+=		:p5-DateTime-Locale>=0.41:converters/p5-DateTime-Locale

.include <bsd.port.mk>
