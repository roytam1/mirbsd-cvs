# $OpenBSD: Makefile,v 1.1.1.1 2003/05/23 21:13:15 avsm Exp $

COMMENT=	"classes to represent XML data in PHP"

V=		1.1
DISTNAME=	XML_Tree-${V}
PKGNAME=	pear-XML-Tree-${V}
CATEGORIES=	textproc pear

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
