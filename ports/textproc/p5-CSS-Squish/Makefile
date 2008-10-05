# $MirOS: ports/textproc/p5-Text-Quoted/Makefile,v 1.1 2008/10/04 20:30:57 bsiegert Exp $

COMMENT=		compact many CSS files into one big file
DISTNAME=		CSS-Squish-0.07
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		textproc perl5

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=CSS/}

# Perl
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

B_R_DEPENDS+=		::www/p5-URI
B_R_DEPENDS+=		::devel/p5-Test-LongString

CONFIGURE_STYLE=	perl

.include <bsd.port.mk>
