# $MirOS: ports/misc/p5-CreditCard/Makefile,v 1.1.7.1 2005/03/18 15:50:32 tg Exp $
# $OpenBSD: Makefile,v 1.8 2002/12/29 19:49:40 fgsch Exp $

COMMENT=			verify credit card pins
DISTNAME=	Business-CreditCard-0.21
CATEGORIES=	misc perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=Business/}

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	perl

NO_REGRESS=		Yes

do-configure:

do-build:
	@cd ${WRKSRC} && pod2man CreditCard.pm > Business::CreditCard.3p

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/${P5SITE}/Business
	${INSTALL_DATA} ${WRKSRC}/CreditCard.pm ${PREFIX}/${P5SITE}/Business/
	${INSTALL_MAN_DIR} ${PREFIX}/man/man3/
	${INSTALL_MAN} ${WRKSRC}/Business::CreditCard.3p ${PREFIX}/man/man3/

.include <bsd.port.mk>
