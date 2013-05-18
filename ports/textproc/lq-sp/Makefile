# $OpenBSD: Makefile,v 1.5 2004/01/14 19:04:49 naddy Exp $

COMMENT=	"SGML parser and entity manager"

DISTNAME=	lq-sp-1.3.4.10
CATEGORIES=	textproc
HOMEPAGE=	http://www.htmlhelp.com/tools/validator/offline/


# BSD-like
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${HOMEPAGE}
CXXFLAGS+=		-fno-implicit-templates

NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/nsgmls/lq-nsgmls ${PREFIX}/bin

.include <bsd.port.mk>
