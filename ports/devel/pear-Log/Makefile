# $OpenBSD: Makefile,v 1.5 2004/02/29 00:08:50 avsm Exp $

COMMENT=	"logging utilities for PHP"

V=		1.8.4
DISTNAME=	Log-${V}
PKGNAME=	pear-${DISTNAME}
CATEGORIES=	devel pear

MASTER_SITES=	http://pear.php.net/get/
EXTRACT_SUFX=	.tgz

HOMEPAGE=	http://www.csh.rit.edu/~jon/projects/pear_log/

FLAVORS=	php4 php5
FLAVOR?=	php5

.if ${FLAVOR:L} == "php4"
MODULES=	www/php4/pear
.elif ${FLAVOR:L} == "php5"
MODULES=	www/php5/pear
.else
ERRORS+=	'Error: choose either php4 or php5 flavour'
.endif

# PHP License
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <bsd.port.mk>
