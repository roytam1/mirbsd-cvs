# $MirOS$
# $OpenBSD: Makefile,v 1.8 2002/10/30 04:13:36 pvalchev Exp $

COMMENT=	perl module for accessing NNTP articles

DISTNAME=	News-Article-1.13
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	news perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=News/}


BUILD_DEPENDS=	:p5-PGP-Sign-*:security/p5-PGP-Sign
RUN_DEPENDS=	${BUILD_DEPENDS}

PERMIT_PACKAGE_CDROM=	dependency security/gnupg is not allowed for CDROM
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= perl
USE_CXX=	Yes # depends on gnupg, which uses CXX

.include <bsd.port.mk>
