# $MirOS: ports/mailnews/pear-Mail-Mime/Makefile,v 1.5 2007/04/12 20:23:46 bsiegert Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/04/03 10:36:22 avsm Exp $

COMMENT=			classes to create and decode MIME messages in PHP

VSN=		1.2.1
DISTNAME=	Mail_Mime-${VSN}
PKGNAME=	pear-Mail-Mime-${VSN}-${DASH_VER}
CATEGORIES=	mail pear

MASTER_SITES=	http://pear.php.net/get/
EXTRACT_SUFX=	.tgz

MODULES=	www/php/pear

# PHP License
PERMIT_PACKAGE_CDROM=	dependency www/php/core is not allowed for CDROM
PERMIT_PACKAGE_FTP=	dependency www/php/core is not allowed for FTP
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <bsd.port.mk>
