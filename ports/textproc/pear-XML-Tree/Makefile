# $MirOS: ports/textproc/pear-XML-Tree/Makefile,v 1.5 2007/04/16 18:56:21 bsiegert Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/05/23 21:13:15 avsm Exp $

COMMENT=			classes to represent XML data in PHP

VSN=		1.1
DISTNAME=	XML_Tree-${VSN}
PKGNAME=	pear-XML-Tree-${VSN}-${DASH_VER}
CATEGORIES=	textproc pear

MASTER_SITES=	http://pear.php.net/get/
EXTRACT_SUFX=	.tgz

MODULES=	www/php/pear

# PHP License
PERMIT_PACKAGE_CDROM=	dependency www/php/core is not allowed for CDROM
PERMIT_PACKAGE_FTP=	dependency www/php/core is not allowed for FTP
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <bsd.port.mk>
