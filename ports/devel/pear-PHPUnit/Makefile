# $OpenBSD: Makefile,v 1.2 2004/02/29 00:34:01 avsm Exp $

COMMENT=	"regression testing framework for PHP"

V=		0.6.2
DISTNAME=	PHPUnit-${V}
PKGNAME=	pear-${DISTNAME}
CATEGORIES=	devel pear

MASTER_SITES=	http://pear.php.net/get/
EXTRACT_SUFX=	.tgz

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
