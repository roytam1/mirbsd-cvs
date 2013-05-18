# $OpenBSD: Makefile,v 1.4 2004/01/30 08:39:49 xsa Exp $

COMMENT=	"geek code generator"

DISTNAME=	geekcode-1.7.3
CATEGORIES=	misc

HOMEPAGE=	http://geekcode.sourceforge.net/
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=geekcode/}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/geekcode ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/geekcode
	${INSTALL_DATA} ${WRKSRC}/geekcode.txt ${PREFIX}/share/doc/geekcode

.include <bsd.port.mk> 
