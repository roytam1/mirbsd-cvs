# $MirOS: ports/mailnews/p5-Mail-Audit/Makefile,v 1.2 2005/07/07 21:22:56 bsiegert Exp $
# $OpenBSD: Makefile,v 1.4 2004/01/30 17:04:48 lebel Exp $

COMMENT=			library for creating easy mail filters
DISTNAME=	Mail-Audit-2.1
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	mail perl5
HOMEPAGE=	http://simon-cozens.org/writings/mail-audit.html

# GPL/Artistic licence
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=Mail/}

BUILD_DEPENDS=    	:p5-Mail-Tools-*:mailnews/p5-Mail-Tools
RUN_DEPENDS=    	:p5-Mail-Tools-*:mailnews/p5-Mail-Tools

CONFIGURE_STYLE= 	perl

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/Mail-Audit
	${INSTALL_DATA} ${WRKSRC}/FAQ ${PREFIX}/share/doc/Mail-Audit

.include <bsd.port.mk>
