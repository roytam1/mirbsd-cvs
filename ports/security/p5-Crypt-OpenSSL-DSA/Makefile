# $OpenBSD: Makefile,v 1.3 2004/01/17 15:58:09 naddy Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			implements DSA using OpenSSL

VERSION=	0.11
DISTNAME=	Crypt-OpenSSL-DSA-${VERSION}
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	security perl5
HOMEPAGE=	http://perl-openssl.sourceforge.net/
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=Crypt/}


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

BUILD_DEPENDS=		:p5-Crypt-OpenSSL-Random->=0.03:security/p5-Crypt-OpenSSL-Random
RUN_DEPENDS=		${BUILD_DEPENDS}

CONFIGURE_STYLE=	perl

.include <bsd.port.mk>
