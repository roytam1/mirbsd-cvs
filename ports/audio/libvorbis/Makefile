# $MirOS: ports/audio/libvorbis/Makefile,v 1.5 2006/09/14 00:07:05 tg Exp $
# $OpenBSD: Makefile,v 1.13 2003/12/14 00:52:22 naddy Exp $

COMMENT=		audio compression codec library
DISTNAME=		libvorbis-1.1.2
CATEGORIES=    		audio
HOMEPAGE=		http://www.vorbis.com/

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://downloads.xiph.org/releases/vorbis/
LIB_DEPENDS+=		ogg::audio/libogg
MODULES+=		devel/pkgconfig

CONFIGURE_STYLE=	autogen
AUTOMAKE_VERSION=	1.9
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--disable-dependency-tracking \
			--disable-libtool-lock \
			--with-ogg=${LOCALBASE}

.include <bsd.port.mk>
