# $OpenBSD: Makefile,v 1.13 2004/04/05 12:42:32 xsa Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			checks HTML documents for broken links

DISTNAME=	linkchecker-1.12.2
CATEGORIES=    	www

HOMEPAGE=	http://linkchecker.sourceforge.net/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=linkchecker/}

MODULES=	lang/python

MODPY_DISTUTILS_INSTALLARGS=	--no-compile

BUILD_DEPENDS+=	:py-dns-*:net/py-dns

NO_REGRESS=	Yes

post-install:
	@chmod ${MANMODE} ${PREFIX}/man/man1/linkchecker.1

.include <bsd.port.mk>
