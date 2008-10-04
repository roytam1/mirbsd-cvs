# $MirOS: ports/archivers/p5-Compress-Zlib/Makefile,v 1.5 2006/09/14 00:06:51 tg Exp $

COMMENT=		perl interface to the bzip2 compression library
DISTNAME=		Compress-Bzip2-2.09
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		archivers perl5

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=Compress/}

LIB_DEPENDS+=		bz2::archivers/bzip2

# Perl
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

CONFIGURE_STYLE=	 perl

.include <bsd.port.mk>
