# $MirOS: ports/chinese/py-zhCodecs/Makefile,v 1.2 2005/07/07 21:17:55 bsiegert Exp $
# $OpenBSD: Makefile,v 1.5 2003/10/13 16:24:27 sturm Exp $

COMMENT=			Python Unicode codecs for Chinese charsets

VERSION=	1.2.0
DISTNAME=	ChineseCodecs${VERSION}
PKGNAME=	py-zhCodecs-${VERSION}-0
CATEGORIES=    	chinese devel

HOMEPAGE=	http://sourceforge.net/projects/python-codecs/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.shellhung.org/pub/OpenBSD/packages/chinese/

USE_CXX=	Yes
MODULES=	lang/python

MODPY_DISTUTILS_INSTALLARGS=	-O1

WRKSRC=	${WRKDIST}/Python

NO_REGRESS=	Yes

post-extract:
	@${CHMOD} 711 ${WRKSRC}/chinesetw

.include <bsd.port.mk>
