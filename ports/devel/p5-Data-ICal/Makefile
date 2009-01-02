# $MirOS: ports/infrastructure/templates/perlmod.Makefile,v 1.1 2009/01/01 17:11:33 bsiegert Exp $

COMMENT=		generates iCalendar (RFC 2445) calendar files
DISTNAME=		Data-ICal-0.13
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		devel perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=../../authors/id/J/JE/JESSE}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	perl

B_R_DEPENDS+=		::textproc/p5-Text-vFile-asData
B_R_DEPENDS+=		::devel/p5-Class-ReturnValue
B_R_DEPENDS+=		::devel/p5-Test-Warn
B_R_DEPENDS+=		::converters/p5-MIME-Base64
B_R_DEPENDS+=		::devel/p5-Test-LongString
B_R_DEPENDS+=		::devel/p5-Class-Accessor
B_R_DEPENDS+=		::devel/p5-Test-NoWarnings

PKG_ARCH=		*

.include <bsd.port.mk>
