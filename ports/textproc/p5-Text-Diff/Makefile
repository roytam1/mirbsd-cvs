# $MirOS: ports/archivers/p5-IO-Compress-Base/Makefile,v 1.1 2008/11/09 17:10:15 bsiegert Exp $

COMMENT=		perform diffs on files and record sets
DISTNAME=		Text-Diff-0.35
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		textproc perl5

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=Text/}

# Perl
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

B_R_DEPENDS+=		::devel/p5-Algorithm-Diff

CONFIGURE_STYLE=	perl
PKG_ARCH=		*

.include <bsd.port.mk>
