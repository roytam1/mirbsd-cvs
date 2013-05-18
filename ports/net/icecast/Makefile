# $MirOS: ports/net/icecast/Makefile,v 1.1.7.1 2005/03/18 15:48:21 tg Exp $
# $OpenBSD: Makefile,v 1.24 2004/05/13 10:48:36 naddy Exp $

COMMENT=	"server for streaming Ogg Vorbis and MP3"

DISTNAME=	icecast-2.2.0
CATEGORIES=	net audio

HOMEPAGE=	http://www.icecast.org/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	http://downloads.us.xiph.org/releases/icecast/

CONFIGURE_STYLE= autoconf
AUTOCONF_NEW=	yes
CONFIGURE_ARGS+= --localstatedir=/var --without-theora
CONFIGURE_ENV=	CPPFLAGS="-I${LOCALBASE}/include" \
		LDFLAGS="-L${LOCALBASE}/lib"

LIB_DEPENDS=	curl.2::net/curl \
		xslt.1::textproc/libxslt \
		vorbis.2,vorbisenc.2::audio/libvorbis


post-build:
	@sed -e 's,##PREFIX##,${TRUEPREFIX},g' < ${FILESDIR}/README.OpenBSD > \
		${WRKBUILD}/README.OpenBSD

post-install:
	${INSTALL_DATA} ${WRKBUILD}/README.OpenBSD \
		${PREFIX}/share/doc/icecast/README.OpenBSD

.include <bsd.port.mk>
