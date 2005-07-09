# $OpenBSD: Makefile,v 1.4 2005/03/08 10:04:45 alek Exp $

COMMENT=		"Open video codec"
DISTNAME=		libtheora-1.0alpha4
CATEGORIES=		multimedia
HOMEPAGE=		http://www.theora.org

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://downloads.xiph.org/releases/theora/

#BUILD_DEPENDS=		::devel/pkgconfig
LIB_DEPENDS=        	::audio/libogg \
			::audio/libvorbis

USE_X11=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--disable-dependency-tracking \
			--disable-player

.include <bsd.port.mk>
