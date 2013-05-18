# $MirOS: ports/textproc/pear-XML-Tree/Makefile,v 1.4 2006/09/14 00:14:20 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/05/23 21:13:15 avsm Exp $

COMMENT=			classes to represent XML data in PHP

V=		1.1
DISTNAME=	XML_Tree-${V}
PKGNAME=	pear-XML-Tree-${V}-0
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
