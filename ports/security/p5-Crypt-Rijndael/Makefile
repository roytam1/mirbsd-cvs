# $OpenBSD: Makefile,v 1.3 2004/01/17 15:58:09 naddy Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			interface to the rijndael encryption algorithm aka AES

DISTNAME=	Crypt-Rijndael-0.05
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	security perl5


# LGPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=Crypt/}

CONFIGURE_STYLE= perl

.include <bsd.port.mk>	
