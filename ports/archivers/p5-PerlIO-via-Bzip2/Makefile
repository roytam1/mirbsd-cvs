# $MirOS$

COMMENT=	PerlIO layer for bzip2 (de)compression
VERSION=	0.02
DISTNAME=	PerlIO-via-Bzip2-${VERSION}
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	archivers sysutils perl5

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=PerlIO/}

B_R_DEPENDS+=	::archivers/p5-Compress-Bzip2

# Perl
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

CONFIGURE_STYLE= perl

.include <bsd.port.mk>
