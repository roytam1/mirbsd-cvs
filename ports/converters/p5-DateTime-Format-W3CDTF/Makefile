# $MirOS: ports/infrastructure/templates/perlmod.Makefile,v 1.2 2009/01/04 17:20:07 bsiegert Exp $

COMMENT=		parse and format W3CDTF datetime strings
DISTNAME=		DateTime-Format-W3CDTF-0.04
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		converters perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=../../authors/id/K/KE/KELLAN/}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	perl

B_R_DEPENDS+=		::converters/p5-DateTime

PKG_ARCH=		*

.include <bsd.port.mk>
