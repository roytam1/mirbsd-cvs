# $MirOS: ports/devel/p5-Calendar-Simple/Makefile,v 1.1 2008/10/30 20:53:11 bsiegert Exp $

COMMENT=		locate per-dist and per-module shared files

DISTNAME=		File-ShareDir-1.00
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		devel perl5 

# like Perl (GPL/Artistic)
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=File/}

B_R_DEPENDS+=		::devel/p5-Class-Inspector
B_R_DEPENDS+=		::devel/p5-Params-Util

CONFIGURE_STYLE=	perl
PKG_ARCH=		*

.include <bsd.port.mk>
