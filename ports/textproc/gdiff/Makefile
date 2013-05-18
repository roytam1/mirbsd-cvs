# $MirOS$
# $OpenBSD: Makefile,v 1.6 2004/02/25 13:59:07 naddy Exp $

COMMENT=		GNU versions of the diff utilities
VERSION=		2.8.1
DASH_VER=		1
DISTNAME=		diffutils-${VERSION}
PKGNAME=		gdiff-${VERSION}-${DASH_VER}
CATEGORIES=		textproc
HOMEPAGE=		http://www.gnu.org/software/diffutils/
MASTER_SITES=		${MASTER_SITE_GNU:=diffutils/}

# GPL
PERMIT_PACKAGE_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--program-prefix=g \
			--disable-nls

.include <bsd.port.mk>
