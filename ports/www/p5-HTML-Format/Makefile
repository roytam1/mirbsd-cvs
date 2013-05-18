# $MirOS$
# $OpenBSD: Makefile,v 1.6 2003/10/18 19:44:53 sturm Exp $

COMMENT=		html text formating class

DISTNAME=		HTML-Format-1.23
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		devel perl5 

# GPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=HTML/}

B_R_DEPENDS+=		:p5-HTML-Tree-*:www/p5-HTML-Tree
B_R_DEPENDS+=		:p5-Font-AFM->=1.17:textproc/p5-Font-AFM

CONFIGURE_STYLE=	perl

.include <bsd.port.mk>
