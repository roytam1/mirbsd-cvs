# $MirOS: ports/infrastructure/templates/perlmod.Makefile,v 1.1 2009/01/01 17:11:33 bsiegert Exp $

COMMENT=		concise attribute rewriting
DISTNAME=		HTML-RewriteAttributes-0.03
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		www perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=../../authors/id/S/SA/SARTAK}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	perl

B_R_DEPENDS+=		::www/p5-HTML-Tagset
B_R_DEPENDS+=		::www/p5-HTML-Parser
B_R_DEPENDS+=		::www/p5-URI

PKG_ARCH=		*

.include <bsd.port.mk>
