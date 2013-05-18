# $MirOS: ports/audio/mp3blaster/Makefile,v 1.2 2005/06/23 16:51:13 tg Exp $
# $OpenBSD: Makefile,v 1.5 2003/12/01 19:18:19 naddy Exp $

COMMENT=			text console audio player with an interactive interface
DISTNAME=		mp3blaster-3.2.0
CATEGORIES=		audio
HOMEPAGE=		http://www.stack.nl/~brama/mp3blaster/
MASTER_SITES=		${HOMEPAGE}src/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=		sidplay.1::audio/libsidplay \
			vorbis.1,vorbisfile.2::audio/libvorbis

USE_CXX=		Yes
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS=		--with-cxxflags="${CXXFLAGS}"

.include <bsd.port.mk>
