# $MirOS: ports/x11/fluxbox/Makefile,v 1.2 2006/02/02 01:41:58 tg Exp $
# $OpenBSD: Makefile,v 1.36 2006/01/25 03:57:43 david Exp $

COMMENT=			window manager based on the original Blackbox code
VERSION=		0.9.14
DISTNAME=		fluxbox-${VERSION}
CATEGORIES=		x11
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=fluxbox/}
HOMEPAGE=		http://fluxbox.org/

# X11
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS=		--enable-xinerama --enable-imlib2
CONFIGURE_ARGS+=	--disable-nls --disable-dependency-tracking \
			--disable-libtool-lock

USE_CXX=		Yes
USE_X11=		Yes
NO_REGRESS=		Yes
MODULES+=		devel/pkgconfig
LIB_DEPENDS=		Imlib2::graphics/imlib2

.include <bsd.port.mk>
