# $MirOS: ports/archivers/p5-IO-Compress-Base/Makefile,v 1.1 2008/11/09 17:10:15 bsiegert Exp $

COMMENT=		read and write gzip-compressed buffers
DISTNAME=		IO-Compress-Zlib-2.015
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		archivers perl5

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=IO/}

# Perl
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

B_R_DEPENDS+=		:p5-Compress-Raw-Zlib->=2.015:archivers/p5-Compress-Raw-Zlib
B_R_DEPENDS+=		:p5-IO-Compress-Base->=2.015:archivers/p5-IO-Compress-Base
B_R_DEPENDS+=		:p5-IO-Compress-Bzip2->=2.015:archivers/p5-IO-Compress-Bzip2

CONFIGURE_STYLE=	perl
PKG_ARCH=		*

.include <bsd.port.mk>
