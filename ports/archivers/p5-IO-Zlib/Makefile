# $MirOS$
# $OpenBSD: Makefile,v 1.3 2003/06/04 22:16:22 jolan Exp $

COMMENT=		IO:: style interface to Compress::Zlib

DISTNAME=		IO-Zlib-1.09
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		archivers perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=IO/}


# Perl
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

B_R_DEPENDS=		:p5-Compress-Zlib->=2.015:archivers/p5-Compress-Zlib

CONFIGURE_STYLE=	perl

.include <bsd.port.mk>
