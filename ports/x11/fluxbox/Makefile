# $MirOS$
# $OpenBSD: Makefile,v 1.30 2004/04/29 17:30:15 robert Exp $

COMMENT=		"window manager based on the original Blackbox code"

VERSION=		20040715
DISTNAME=		fluxbox-${VERSION}
CATEGORIES=		x11
EXTRACT_SUFX=		.tar.bz2

MASTER_SITES=		${MASTER_SITE_MIRBSD}

HOMEPAGE=		http://fluxbox.org/

# X11
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

WRKDIST=		${WRKDIR}/fluxbox
CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS=		--enable-kde --enable-xinerama --disable-nls
USE_CXX=		Yes
USE_GMAKE=		Yes
USE_X11=		Yes

BUILD_DEPENDS=		:pkgconfig-*:devel/pkgconfig

#CONFIGURE_ENV=		CPPFLAGS="-I${LOCALBASE}/include" \
#			LDFLAGS="-L${LOCALBASE}/lib" \
#			PKG_CONFIG_PATH="${X11BASE}/lib/pkgconfig"

pre-build:
	cd ${WRKSRC}/src && gmake defaults.hh

.include <bsd.port.mk>
