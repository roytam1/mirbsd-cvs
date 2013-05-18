# $MirOS$
# $OpenBSD: Makefile,v 1.8 2004/04/12 10:17:00 xsa Exp $

COMMENT=		perl interface to tar archives
VERSION=		1.40
DISTNAME=		Archive-Tar-${VERSION}
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		archivers perl5

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=Archive/}

# Perl
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

B_R_DEPENDS=		:p5-IO-Zlib->=1.01:archivers/p5-IO-Zlib
B_R_DEPENDS=		::textproc/p5-Text-Diff
B_R_DEPENDS=		::devel/p5-Package-Constants

CONFIGURE_STYLE= 	perl
CONFIGURE_ARGS+=	-d

.include <bsd.port.mk>
