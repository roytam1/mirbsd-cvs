# $MirOS: ports/devel/pear-Log/Makefile,v 1.5 2007/04/07 14:35:03 bsiegert Exp $
# $OpenBSD: Makefile,v 1.5 2004/02/29 00:08:50 avsm Exp $

COMMENT=	logging utilities for PHP

VSN=		1.8.4
DISTNAME=	Log-${VSN}
PKGNAME=	pear-${DISTNAME}-${DASH_VER}
CATEGORIES=	devel pear

MASTER_SITES=	http://pear.php.net/get/
EXTRACT_SUFX=	.tgz

HOMEPAGE=	http://www.csh.rit.edu/~jon/projects/pear_log/

MODULES=	www/php/pear

# PHP License
PERMIT_PACKAGE_CDROM=	dependency www/php is non-free
PERMIT_PACKAGE_FTP=	dependency www/php is non-free
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <bsd.port.mk>
