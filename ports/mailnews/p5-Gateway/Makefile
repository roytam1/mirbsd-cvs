# $MirOS: ports/mailnews/p5-Gateway/Makefile,v 1.3 2006/09/14 00:10:40 tg Exp $
# $OpenBSD: Makefile,v 1.9 2002/10/30 04:13:36 pvalchev Exp $

COMMENT=	perl module to gateway between news and mail
DISTNAME=	Gateway-0.42
PKGNAME=	p5-${DISTNAME}-${DASH_VER}
CATEGORIES=	news perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=News/}

B_R_DEPENDS=	:p5-PGP-Sign-*:security/p5-PGP-Sign \
		:p5-News-Article->=1.07:mailnews/p5-News-Article

PERMIT_PACKAGE_CDROM=	dependency security/gnupg is not allowed for CDROM
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= perl
USE_CXX=	Yes # depends on libusb, which uses CXX

# install example files
post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/p5-Gateway
	${INSTALL_DATA} ${WRKSRC}/examples/*  \
		${PREFIX}/share/examples/p5-Gateway

.include <bsd.port.mk>
