# $MirOS: ports/devel/p5-Tree-Simple/Makefile,v 1.1 2008/10/13 21:21:16 bsiegert Exp $

COMMENT=		perl extension for scrubbing/sanitizing html

DISTNAME=		HTML-Scrubber-0.08
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		www perl5 

# like Perl (GPL/Artistic)
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=HTML/}

B_R_DEPENDS=		:p5-HTML-Parser->=3:www/p5-HTML-Parser

CONFIGURE_STYLE=	perl
PKG_ARCH=		*

.include <bsd.port.mk>
