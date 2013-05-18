# $MirOS: ports/www/p5-HTML-Base/Makefile,v 1.2 2005/07/07 21:28:00 bsiegert Exp $
# $OpenBSD: Makefile,v 1.9 2003/10/18 19:44:52 sturm Exp $

COMMENT=			base HTML library
DISTNAME=	HTML-0.6
PKGNAME=	p5-HTML-Base-0.6-0
CATEGORIES=	www perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=HTML/}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	perl

NO_REGRESS=	Yes

WRKDIST=	${WRKDIR}

do-configure:

do-build:
	cd ${WRKSRC} && pod2man html_base.pod HTML::Base.3p

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/${P5ARCH}/HTML
	${INSTALL_DATA} ${WRKSRC}/HTML/Base.pm \
		${PREFIX}/${P5ARCH}/HTML/
	${INSTALL_MAN_DIR} ${PREFIX}/man/man3/
	${INSTALL_MAN} ${WRKSRC}/HTML::Base.3p ${PREFIX}/man/man3/

.include <bsd.port.mk>
