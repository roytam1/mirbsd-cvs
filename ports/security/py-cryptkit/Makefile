# $OpenBSD: Makefile,v 1.7 2004/02/09 09:34:14 xsa Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			Python Cryptographic Toolkit

DISTNAME=	cryptkit-0.9
PKGNAME=	py-${DISTNAME}-0
CATEGORIES=    	security devel

HOMEPAGE=	http://eevolved.com/cryptkit/


# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=cryptkit/}

MODULES=	lang/python

NO_REGRESS=	Yes

.include <bsd.port.mk>
