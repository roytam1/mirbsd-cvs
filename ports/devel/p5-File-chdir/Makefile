# $MirOS: ports/devel/p5-File-chdir/Makefile,v 1.1 2007/10/09 22:06:56 bsiegert Exp $

COMMENT=		more sensible way to change directories
DISTNAME=		File-chdir-0.1001
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		devel perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=File/}
HOMEPAGE=		http://search.cpan.org/~dagolden/${DISTNAME}/

# like Perl
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

B_R_DEPENDS+=		::devel/p5-PathTools

CONFIGURE_STYLE=	perl

.include <bsd.port.mk>
