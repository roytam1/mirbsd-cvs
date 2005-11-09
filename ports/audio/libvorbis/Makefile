# $MirOS: ports/audio/libvorbis/Makefile,v 1.1.7.1 2005/03/18 15:42:58 tg Exp $
# $OpenBSD: Makefile,v 1.13 2003/12/14 00:52:22 naddy Exp $

COMMENT=	"audio compression codec library"
DISTNAME=	libvorbis-1.1.1
CATEGORIES=    	audio
HOMEPAGE=	http://www.xiph.org/ogg/vorbis/

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	http://downloads.xiph.org/releases/vorbis/

LIB_DEPENDS=	ogg::audio/libogg

CONFIGURE_STYLE=autogen
AUTOMAKE_VERSION=1.9
AUTOCONF_NEW=	Yes
CONFIGURE_ARGS=	${CONFIGURE_SHARED} --with-ogg=${LOCALBASE}
SEPARATE_BUILD=	simple

.include <bsd.port.mk>
