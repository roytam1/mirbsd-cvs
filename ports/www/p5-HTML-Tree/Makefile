# $MirOS$
# $OpenBSD: Makefile,v 1.13 2003/11/03 01:07:13 margarida Exp $

COMMENT=		perl parser that builds an HTML tree

VERSION=		3.23
DISTNAME=		HTML-Tree-${VERSION}
PKGNAME=		p5-${DISTNAME}-0
CATEGORIES=		www perl5

HOMEPAGE=		http://www.speech.cs.cmu.edu/~sburke/
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=HTML/}

# Artistic
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

B_R_DEPENDS+=		:p5-HTML-Parser->=3.46:www/p5-HTML-Parser
B_R_DEPENDS+=		:p5-HTML-Tagset->=3.02:www/p5-HTML-Tagset

CONFIGURE_STYLE= perl

.include <bsd.port.mk>
