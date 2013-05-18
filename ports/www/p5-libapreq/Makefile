# $MirOS: ports/www/p5-libapreq/Makefile,v 1.3 2005/07/07 21:28:11 bsiegert Exp $
# $OpenBSD: Makefile,v 1.3 2004/04/16 22:32:27 naddy Exp $

BROKEN=		"mod_perl.pm nonexistent (wtf?)"

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}
COMMENT=			Generic Apache Request Library
DISTNAME=	libapreq-1.3
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	www perl5
HOMEPAGE=	http://httpd.apache.org/apreq/

# Apache Software License
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=Apache/}
BUILD_DEPENDS=	:mod_perl-*:www/mod_perl \
		:p5-Apache-Test-*:www/p5-Apache-Test

RUN_DEPENDS=	:mod_perl-*:www/mod_perl

CONFIGURE_STYLE=perl

# XXX broken, see p5-Apache-Test
NO_REGRESS=	Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/p5-libapreq
	@cp -R ${WRKSRC}/eg/* ${PREFIX}/share/examples/p5-libapreq
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/libapreq
	${INSTALL_DATA} ${WRKSRC}/LICENSE ${PREFIX}/share/doc/libapreq

.include <bsd.port.mk>
