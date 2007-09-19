# $MirOS: ports/sysutils/p5-PerlIO-via-dynamic/Makefile,v 1.1 2007/09/15 23:42:56 bsiegert Exp $

COMMENT=		calculate digests while reading or writing
DISTNAME=		IO-Digest-0.10
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		sysutils perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=IO/}
HOMEPAGE=		http://search.cpan.org/~clk/${DISTNAME}/

B_R_DEPENDS+=		::sysutils/p5-PerlIO-via-dynamic

# like Perl (GPL/Artistic)
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	perl

.include <bsd.port.mk>
