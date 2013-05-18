# $MirOS: ports/infrastructure/templates/perlmod.Makefile,v 1.2 2009/01/04 17:20:07 bsiegert Exp $

COMMENT=		creates and updates RSS files
DISTNAME=		XML-RSS-1.41
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		textproc perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=../../authors/id/S/SH/SHLOMIF/}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	perl

B_R_DEPENDS+=		:p5-XML-Parser>=2.23:textproc/p5-XML-Parser
B_R_DEPENDS+=		:p5-Test-Manifest>=0.9:devel/p5-Test-Manifest
B_R_DEPENDS+=		::converters/p5-DateTime-Format-Mail
B_R_DEPENDS+=		::www/p5-HTML-Parser
B_R_DEPENDS+=		::converters/p5-DateTime
B_R_DEPENDS+=		::converters/p5-DateTime-Format-W3CDTF

PKG_ARCH=		*

.include <bsd.port.mk>
