# $MirOS: ports/devel/pear-PHPUnit/Makefile,v 1.6 2008/10/16 19:43:49 tg Exp $
# $OpenBSD: Makefile,v 1.2 2004/02/29 00:34:01 avsm Exp $

BROKEN=			distfile is unfetchable

COMMENT=	regression testing framework for PHP

VSN=		0.6.2
DISTNAME=	PHPUnit-${VSN}
PKGNAME=	pear-${DISTNAME}-${DASH_VER}
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
