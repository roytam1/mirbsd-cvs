# $OpenBSD: Makefile,v 1.2 2004/01/30 08:39:49 xsa Exp $

COMMENT=			module to interact with a Cisco router

DISTNAME=		Net-Telnet-Cisco-1.10
PKGNAME=		p5-${DISTNAME}-0
CATEGORIES=		net perl5

HOMEPAGE=		http://nettelnetcisco.sourceforge.net/

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=Net/}

# Artistic
PERMIT_PACKAGE_CDROM=	Yes	
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	perl

BUILD_DEPENDS=		:p5-Net-Telnet->=3.02:net/p5-Net-Telnet \
			:p5-Term-ReadKey->=2.14:devel/p5-Term-ReadKey

RUN_DEPENDS=		${BUILD_DEPENDS}

.include <bsd.port.mk>
