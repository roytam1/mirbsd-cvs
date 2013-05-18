# $MirOS: ports/devel/pear-Date/Makefile,v 1.6 2007/04/07 14:35:03 bsiegert Exp $
# $OpenBSD: Makefile,v 1.2 2004/02/29 00:09:28 avsm Exp $

COMMENT=	date and timezone classes for PHP

VSN=		1.4.1
DISTNAME=	Date-${VSN}
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
