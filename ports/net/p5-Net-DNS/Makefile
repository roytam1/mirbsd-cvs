# $OpenBSD: Makefile,v 1.24 2004/04/18 20:09:57 wilfried Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			module to interface the DNS resolver

DISTNAME=		Net-DNS-0.47
PKGNAME=		p5-${DISTNAME}-0
CATEGORIES=		net perl5
NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

HOMEPAGE=		http://www.net-dns.org/


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=Net/} \
			${HOMEPAGE}/download/

BUILD_DEPENDS=		${RUN_DEPENDS}
RUN_DEPENDS=		:p5-Digest-HMAC->=1.00:security/p5-Digest-HMAC

CONFIGURE_STYLE=	perl
CONFIGURE_ARGS=		--online-tests

.include <bsd.port.mk>
