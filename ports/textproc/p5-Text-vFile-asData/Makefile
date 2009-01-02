# $MirOS: ports/infrastructure/templates/perlmod.Makefile,v 1.1 2009/01/01 17:11:33 bsiegert Exp $

COMMENT=		parse vFile formatted files into data structures
DISTNAME=		Text-vFile-asData-0.05
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		textproc perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=../../authors/id/R/RC/RCLAMP}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	perl

B_R_DEPENDS+=		::devel/p5-Class-Accessor-Chained

PKG_ARCH=		*

.include <bsd.port.mk>
