# $MirOS: ports/devel/p5-Algorithm-Annotate/Makefile,v 1.1 2007/09/15 22:34:57 bsiegert Exp $

COMMENT=		dispatcher module for command line interface programs
DISTNAME=		App-CLI-0.07
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		devel perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=App/}
HOMEPAGE=		http://search.cpan.org/~clk/${DISTNAME}/

# like Perl
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

B_R_DEPENDS+=		::devel/p5-Locale-Maketext-Simple
B_R_DEPENDS+=		::devel/p5-Getopt-Long
B_R_DEPENDS+=		::textproc/p5-Pod-Simple

CONFIGURE_STYLE=	perl

.include <bsd.port.mk>
