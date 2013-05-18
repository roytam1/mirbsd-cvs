# $MirOS: ports/archivers/p5-Compress-Raw-Zlib/Makefile,v 1.1 2008/11/09 17:01:12 bsiegert Exp $

COMMENT=		low-Level Interface to bzip2 compression library
DISTNAME=		Compress-Raw-Bzip2-2.015
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		archivers perl5

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=Compress/}

# Perl
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

LIB_DEPENDS=		bz2::archivers/bzip2

CONFIGURE_STYLE=	perl
CONFIGURE_ENV=		BUILD_BZIP2=0 BZIP2_LIB=${LOCALBASE}/lib \
			BZIP2_INCLUDE=${LOCALBASE}/include

.include <bsd.port.mk>
