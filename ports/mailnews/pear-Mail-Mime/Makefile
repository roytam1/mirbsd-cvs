# $OpenBSD: Makefile,v 1.1.1.1 2003/04/03 10:36:22 avsm Exp $

COMMENT=	"classes to create and decode MIME messages in PHP"

V=		1.2.1
DISTNAME=	Mail_Mime-${V}
PKGNAME=	pear-Mail-Mime-${V}
CATEGORIES=	mail pear

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
