# $MirOS: ports/devel/pear-Config/Makefile,v 1.5 2007/04/07 14:35:02 bsiegert Exp $
# $OpenBSD: Makefile,v 1.2 2004/02/29 00:08:31 avsm Exp $

COMMENT=	configuration file library for PHP

VSN=		1.10
DISTNAME=	Config-${VSN}
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
