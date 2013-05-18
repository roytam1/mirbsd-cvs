# $MirOS: ports/www/p5-HTML-Parser/Makefile,v 1.6 2008/10/13 21:33:30 bsiegert Exp $
# $OpenBSD: Makefile,v 1.24 2004/04/11 14:59:53 brad Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=		parse and extract information from HTML
 
DISTNAME=		HTML-Parser-3.64
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		www perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=HTML/}

B_R_DEPENDS=		:p5-HTML-Tagset->=3:www/p5-HTML-Tagset

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	perl

.include <bsd.port.mk>
