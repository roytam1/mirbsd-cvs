# $MirOS$
# $OpenBSD: Makefile,v 1.3 2003/11/15 20:02:40 avsm Exp $

COMMENT=	"base package for HTML handling in PHP"
V=		1.2.1
DISTNAME=	HTML_Common-${V}
PKGNAME=	pear-HTML-Common-${V}
CATEGORIES=	devel www pear
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
