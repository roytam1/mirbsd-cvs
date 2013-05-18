# $OpenBSD: Makefile,v 1.3 2003/05/04 17:59:35 margarida Exp $

COMMENT=			office suite

VERSION=		3.5.6
DISTNAME=		siag-${VERSION}
CATEGORIES=		x11

HOMEPAGE=		http://siag.nu/

MASTER_SITES=		http://siag.nu/pub/siag/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes

LIB_DEPENDS=		Mowitz.2::x11/mowitz \
			neXtaw.13::x11/neXtaw

CONFIGURE_STYLE=	gnu

CONFIGURE_ARGS+=	--with-docdir=${PREFIX}/share/doc

LDFLAGS+=		-L${WRKBUILD}/common

NO_REGRESS=		Yes

.include <bsd.port.mk>
