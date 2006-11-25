# $MirOS$

NOT_FOR_PLATFORMS=	${NOPIC_PLATFORMS}

HOMEPAGE=		http://audacious-media-player.org/
MASTER_SITES=		http://audacious-media-player.org/release/
EXTRACT_SUFX=		.tgz

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES+=		devel/pkgconfig

USE_X11=		Yes
USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

EXTRA_XAKE_FLAGS=	top_srcdir=${WRKSRC:Q}
