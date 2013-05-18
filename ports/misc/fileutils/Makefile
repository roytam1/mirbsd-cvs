# $OpenBSD: Makefile,v 1.14 2004/02/25 01:35:50 naddy Exp $

COMMENT=			GNU versions of common file management utilities
COMMENT-ls=			colorized GNU 'ls'

V=			4.1
DISTNAME=		fileutils-$V
CATEGORIES=		misc

PKGNAME=		${DISTNAME}p1-0
PKGNAME-ls=		gnuls-$V-0


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNU:=fileutils/}

MODULES=		devel/gettext

USE_GMAKE=		Yes
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS=		--program-prefix=g

MULTI_PACKAGES=		-ls

.include <bsd.port.mk>
