# $MirOS: ports/security/p5-Crypt-SSLeay/Makefile,v 1.5 2006/09/14 00:13:11 tg Exp $
# $OpenBSD: Makefile,v 1.17 2004/05/16 09:44:29 xsa Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=	library to provide LWP https support via OpenSSL

DISTNAME=	Crypt-SSLeay-0.57
PKGNAME=	p5-${DISTNAME}-${DASH_VER}
CATEGORIES=	security perl5

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=Crypt/}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= perl

MODPERL_CONFIG_VARS+=	--default

.include <bsd.port.mk>
