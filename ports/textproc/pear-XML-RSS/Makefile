# $MirOS: ports/textproc/pear-XML-RSS/Makefile,v 1.3 2005/07/07 21:27:21 bsiegert Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/05/23 21:19:29 avsm Exp $

COMMENT=			parser for RDF Site Summary files in PHP

V=		0.9.2
DISTNAME=	XML_RSS-${V}
PKGNAME=	pear-XML-RSS-${V}-0
CATEGORIES=	textproc pear

MASTER_SITES=	http://pear.php.net/get/
EXTRACT_SUFX=	.tgz

MODULES=	www/php/pear

RUN_DEPENDS=	:pear-XML-Tree-*:textproc/pear-XML-Tree

# PHP License
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <bsd.port.mk>
