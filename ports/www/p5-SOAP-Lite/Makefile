# $MirOS: ports/www/p5-SOAP-Lite/Makefile,v 1.2 2005/07/07 21:28:14 bsiegert Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/05/21 18:14:44 avsm Exp $

COMMENT=			client and server-side SOAP implementation
DISTNAME=	SOAP-Lite-0.55
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	www perl5

# Artistic License
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=SOAP/}

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	::mailnews/p5-MIME-tools \
		::www/p5-URI \
		::security/p5-IO-Socket-SSL \
		::security/p5-Crypt-SSLeay \
		::www/p5-libwww \
		::mailnews/p5-MIME-Lite \
		::textproc/p5-XML-Parser \
		::www/mod_perl

CONFIGURE_STYLE=	perl
CONFIGURE_ARGS+=	--noprompt \
			--HTTP-Client --HTTPS-Client \
			--MAILTO-Client --FTP-Client \
			--HTTP-Daemon --HTTP-Apache \
			--noHTTP-FCGI --POP3-Server \
			--IO-Server --noMQ \
			--noJABBER --MIMEParser \
			--TCP --HTTP

.include <bsd.port.mk>
