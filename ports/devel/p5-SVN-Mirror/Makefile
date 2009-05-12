# $MirOS: ports/devel/p5-SVN-Mirror/Makefile,v 1.1 2007/10/11 21:12:15 bsiegert Exp $

COMMENT=		mirror remote to local Subversion repository
DISTNAME=		SVN-Mirror-0.73
DASH_VER=		1
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		devel perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=SVN/}
HOMEPAGE=		http://search.cpan.org/~clk/${DISTNAME}/

# like Perl
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

B_R_DEPENDS+=		:subversion->=1.4.5:devel/subversion
B_R_DEPENDS+=		::devel/p5-Class-Accessor
B_R_DEPENDS+=		::devel/p5-File-chdir
B_R_DEPENDS+=		::devel/p5-SVN-Simple
B_R_DEPENDS+=		::devel/p5-Term-ReadKey
B_R_DEPENDS+=		::devel/p5-Time-TimeDate
B_R_DEPENDS+=		::www/p5-URI

CONFIGURE_STYLE=	perl
CONFIGURE_ARGS+=	--defaultdeps

.include <bsd.port.mk>
