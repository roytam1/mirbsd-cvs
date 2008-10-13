# $MirOS: ports/devel/p5-Algorithm-Diff/Makefile,v 1.4 2007/09/15 14:04:31 bsiegert Exp $

COMMENT=		object-oriented implementation of a simple n-ary tree

DISTNAME=		Tree-Simple-1.18
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		devel perl5 

# like Perl (GPL/Artistic)
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=Tree/}

CONFIGURE_STYLE=	perl
NO_REGRESS=		Yes # need Test:Exception
PKG_ARCH=		*

.include <bsd.port.mk>
