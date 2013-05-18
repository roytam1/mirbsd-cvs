# $MirOS: ports/audio/vorbis-tools/Makefile,v 1.5 2006/02/09 09:35:41 tg Exp $
# $OpenBSD: Makefile,v 1.21 2003/12/14 00:52:22 naddy Exp $

COMMENT=			play, encode, and manage Ogg Vorbis files
DISTNAME=		vorbis-tools-1.1.1
PKGNAME=		${DISTNAME}-1
CATEGORIES=    		audio
HOMEPAGE=		http://www.vorbis.com/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://downloads.xiph.org/releases/vorbis/

USE_CXX=		Yes
LIB_DEPENDS=		ao::audio/libao \
			curl::net/curl \
			FLAC::audio/flac \
			speex::audio/speex \
			vorbis,vorbisenc,vorbisfile::audio/libvorbis

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		yes
CONFIGURE_ENV+=		PTHREAD_CFLAGS="-pthread" PTHREAD_LIBS="-pthread"
CONFIGURE_ARGS+=	--disable-nls

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/vorbis-tools
	${INSTALL_DATA} ${WRKSRC}/ogg123/ogg123rc-example \
	    ${PREFIX}/share/examples/vorbis-tools/ogg123rc

.include <bsd.port.mk>
