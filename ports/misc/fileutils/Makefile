# $OpenBSD: Makefile,v 1.14 2004/02/25 01:35:50 naddy Exp $

BROKEN=			does not use libc getline(3) implementation

COMMENT=		GNU versions of common file management utilities
COMMENT-ls=		colourised GNU 'ls'

VSN=			4.1
DISTNAME=		fileutils-${VSN}
CATEGORIES=		misc

# once VSN is 4.2, get the fuck rid of this!
PKGNAME=		${DISTNAME}p1-${DASH_VER}
PKGNAME-ls=		gnuls-${VSN}-${DASH_VER}


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
