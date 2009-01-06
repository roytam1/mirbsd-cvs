# $MirOS: ports/infrastructure/templates/perlmod.Makefile,v 1.2 2009/01/04 17:20:07 bsiegert Exp $

COMMENT=		convert between DateTime and RFC2822/822 formats
DISTNAME=		DateTime-Format-Mail-0.3001
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		converters perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=../../authors/id/D/DR/DROLSKY/}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	perl modbuild

B_R_DEPENDS+=		:p5-DateTime>=0.1705:converters/p5-DateTime
B_R_DEPENDS+=		:p5-Params-Validate>=0.67:devel/p5-Params-Validate

PKG_ARCH=		*

.include <bsd.port.mk>
