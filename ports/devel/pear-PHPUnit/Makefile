# $MirOS: ports/devel/pear-PHPUnit/Makefile,v 1.5 2007/04/07 14:35:03 bsiegert Exp $
# $OpenBSD: Makefile,v 1.2 2004/02/29 00:34:01 avsm Exp $

BROKEN=			distfile is unfetchable

COMMENT=	regression testing framework for PHP

V=		0.6.2
DISTNAME=	PHPUnit-${V}
PKGNAME=	pear-${DISTNAME}-0
CATEGORIES=	devel pear

MASTER_SITES=	http://pear.php.net/get/
EXTRACT_SUFX=	.tgz

MODULES=	www/php/pear

# PHP License
PERMIT_PACKAGE_CDROM=	dependency www/php is non-free
PERMIT_PACKAGE_FTP=	dependency www/php is non-free
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <bsd.port.mk>
