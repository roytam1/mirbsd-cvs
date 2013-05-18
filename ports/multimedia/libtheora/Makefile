# $MirOS: ports/multimedia/libtheora/Makefile,v 1.2 2005/12/28 16:38:03 tg Exp $
# $OpenBSD: Makefile,v 1.4 2005/03/08 10:04:45 alek Exp $

COMMENT=			Open video codec
DISTNAME=		libtheora-1.0alpha5
CATEGORIES=		multimedia
HOMEPAGE=		http://www.theora.org

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://downloads.xiph.org/releases/theora/

LIB_DEPENDS=        	ogg::audio/libogg \
			vorbis::audio/libvorbis
MODULES+=		devel/pkgconfig

SUBST_VARS+=		DISTNAME
USE_X11=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--disable-dependency-tracking \
			--disable-player

.include <bsd.port.mk>
