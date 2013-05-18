# $OpenBSD: Makefile,v 1.16 2004/01/17 15:58:10 naddy Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			perl module for using OpenSSL

VERSION=	1.23
DISTNAME=	Net_SSLeay.pm-${VERSION}
PKGNAME=	p5-Net-SSLeay-${VERSION}-0
CATEGORIES=	security perl5
NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

HOMEPAGE=	http://www.bacus.pt/Net_SSLeay/index.html
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=Net/}


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= perl

PLDIR=	${PREFIX}/share/examples/p5-Net-SSLeay
SRCDIR=	${WRKSRC}/examples

post-install:
	${INSTALL_DATA_DIR} ${PLDIR}
	${INSTALL_SCRIPT} ${SRCDIR}/*.pl ${PLDIR}/
	${INSTALL_DATA} ${SRCDIR}/req.conf ${PLDIR}/req.conf

.include <bsd.port.mk>
