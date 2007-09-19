# $MirOS: ports/devel/p5-Algorithm-Annotate/Makefile,v 1.1 2007/09/15 22:34:57 bsiegert Exp $

COMMENT=		simple interface for writing a Subversion delta editor
DISTNAME=		SVN-Simple-0.27
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		devel perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=SVN/}
HOMEPAGE=		http://search.cpan.org/~clk/${DISTNAME}/

# like Perl (GPL/Artistic)
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

B_R_DEPENDS+=		:subversion->=1.4.5:devel/subversion

CONFIGURE_STYLE=	perl

.include <bsd.port.mk>
