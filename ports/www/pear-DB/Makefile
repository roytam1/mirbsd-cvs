# $MirOS$

COMMENT=	"OOP database abstraction layer for PHP"
V=		1.6.8
DISTNAME=	DB-${V}
PKGNAME=	pear-DB-${V}
CATEGORIES=	devel www pear
MASTER_SITES=	http://pear.php.net/get/
EXTRACT_SUFX=	.tgz
RESPONSIBLE=	Benedikt Steinbusch <hama@hamazone.de>

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
