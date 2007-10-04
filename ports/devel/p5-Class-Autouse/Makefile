# $MirOS: ports/devel/p5-SVN-Simple/Makefile,v 1.1 2007/09/19 20:38:15 bsiegert Exp $

COMMENT=		load a class the first time you call a method in it
DISTNAME=		Class-Autouse-1.28
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		devel perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=Class/}
HOMEPAGE=		http://search.cpan.org/~adamk/${DISTNAME}/

# like Perl (GPL/Artistic)
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

B_R_DEPENDS+=		::devel/p5-Scalar-List-Utils

CONFIGURE_STYLE=	perl

.include <bsd.port.mk>
