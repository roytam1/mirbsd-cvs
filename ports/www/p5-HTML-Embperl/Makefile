# $OpenBSD: Makefile,v 1.14 2004/01/17 15:58:10 naddy Exp $

BROKEN=			hangs during configure

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=		allows you to embed perl in your HTML documents

VERSION=	1.3.3
DISTNAME=	HTML-Embperl-${VERSION}
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	www perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=HTML/}


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

BUILD_DEPENDS=	:mod_perl->=1.22:www/mod_perl
RUN_DEPENDS=	${BUILD_DEPENDS}

CONFIGURE_STYLE= perl
CONFIGURE_ENV=	EPHTTPD="/usr/sbin/httpd" APACHE_SRC="/usr/lib/apache"

.include <bsd.port.mk>
