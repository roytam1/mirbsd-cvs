# $MirOS: ports/infrastructure/templates/perlmod.Makefile,v 1.1 2009/01/01 17:11:33 bsiegert Exp $

COMMENT=		module for translating Wiki formatted text into other formats
DISTNAME=		Text-WikiFormat-0.79
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		textproc perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=../../authors/id/C/CH/CHROMATIC/}

# like Perl
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	perl

B_R_DEPENDS+=		::www/p5-URI
B_R_DEPENDS+=		:p5-Scalar-List-Utils>=1.14:devel/p5-Scalar-List-Utils

PKG_ARCH=		*

.include <bsd.port.mk>
