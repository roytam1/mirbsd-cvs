# $MirOS: ports/security/p5-Crypt-SSLeay/Makefile,v 1.4 2006/03/24 16:56:54 bsiegert Exp $
# $OpenBSD: Makefile,v 1.17 2004/05/16 09:44:29 xsa Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			library to provide LWP https support via OpenSSL

DISTNAME=	Crypt-SSLeay-0.51
PKGNAME=	p5-${DISTNAME}-1
CATEGORIES=	security perl5

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=Crypt/}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= perl

.include <bsd.port.mk>
