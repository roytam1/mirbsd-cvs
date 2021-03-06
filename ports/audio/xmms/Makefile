# $MirOS: ports/audio/xmms/Makefile,v 1.11 2008/05/07 22:47:54 tg Exp $
# $OpenBSD: Makefile,v 1.33 2004/05/24 13:17:40 robert Exp $

COMMENT=		Multimedia player for the X Window System
COMMENT-esd=		Esound output plugin for XMMS
COMMENT-vorbis=		Ogg Vorbis input plugin for XMMS
COMMENT-mikmod=		Mikmod input plugin for XMMS
COMMENT-mp3=		MP3 input plugin for XMMS

VERSION=		1.2.10
DASH_VER=		3
DISTNAME=		xmms-${VERSION}
PKGNAME-esd=		xmms-esd-${VERSION}-${DASH_VER}
PKGNAME-vorbis=		xmms-vorbis-${VERSION}-${DASH_VER}
PKGNAME-mikmod=		xmms-mikmod-${VERSION}-${DASH_VER}
PKGNAME-mp3=		xmms-mp3-${VERSION}-${DASH_VER}
CATEGORIES=		audio
HOMEPAGE=		http://www.xmms.org

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

VSN=			1.2.x
MASTER_SITES=		${HOMEPAGE}/files/${VSN}/ \
			ftp://ftp.xmms.org/xmms/${VSN}/ \
			ftp://ftp.sunet.se/pub/multimedia/xmms/${VSN}/ \
			ftp://ftp.stealth.net/xmms/${VSN}/

PSEUDO_FLAVOURS=		no_esd no_vorbis no_mikmod no_mp3
FLAVOUR?=
MULTI_PACKAGES=
.if !${FLAVOUR:L:Mno_esd}
MULTI_PACKAGES+=	-esd
.endif
.if !${FLAVOUR:L:Mno_vorbis}
MULTI_PACKAGES+=	-vorbis
.endif
.if !${FLAVOUR:L:Mno_mikmod}
MULTI_PACKAGES+=	-mikmod
.endif
.if !${FLAVOUR:L:Mno_mp3}
MULTI_PACKAGES+=	-mp3
.endif

SUBPACKAGE?=

MODULES=		devel/gettext
RUN_DEPENDS=		:unzip-*:archivers/unzip
LIB_DEPENDS=		gtk.1.2,gdk.1.2::x11/gtk+1 \
			gthread.1.2::devel/glib1\
			xml::textproc/libxml1

USE_X11=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
MODGNU_RECURSE_DIRS=	${WRKSRC}/libxmms ${WRKSRC}
CONFIGURE_ARGS=		${CONFIGURE_SHARED} \
			--without-gnome \
			--enable-ipv6

CONFIGURE_ENV=		XML_CONFIG="${LOCALBASE}/bin/xml-config" \

DOCS=			README NEWS FAQ


.if defined(PACKAGING)
. if ${SUBPACKAGE} == "-esd"
LIB_DEPENDS=		esd::audio/esound
RUN_DEPENDS=		::audio/xmms
. endif
. if ${SUBPACKAGE} == "-vorbis"
LIB_DEPENDS=		vorbis,vorbisfile::audio/libvorbis
RUN_DEPENDS=		::audio/xmms
. endif
. if ${SUBPACKAGE} == "-mikmod"
LIB_DEPENDS=		mikmod::audio/libmikmod
RUN_DEPENDS=		::audio/xmms
. endif
. if ${SUBPACKAGE} == "-mp3"
PERMIT_PACKAGE_CDROM=	"patent issues"
PERMIT_DISTFILES_CDROM= "patent issues"
RUN_DEPENDS=		::audio/xmms
. endif
.else
. if ${MULTI_PACKAGES:M-esd}
LIB_DEPENDS+=		esd::audio/esound
CONFIGURE_ARGS+=	--with-esd-prefix=${LOCALBASE}
. else
CONFIGURE_ARGS+=	--disable-esd
. endif
. if ${MULTI_PACKAGES:M-vorbis}
LIB_DEPENDS+=		vorbis,vorbisfile::audio/libvorbis
CONFIGURE_ARGS+=	--with-ogg-prefix=${LOCALBASE}	\
			--with-vorbis-prefix=${LOCALBASE}
. else
CONFIGURE_ARGS+=	--disable-vorbis
. endif
. if ${MULTI_PACKAGES:M-mikmod}
LIB_DEPENDS+=		mikmod::audio/libmikmod
CONFIGURE_ARGS+=	--with-mikmod-prefix=${LOCALBASE}
. else
CONFIGURE_ARGS+=	--disable-mikmod
. endif
.endif

pre-configure:
	@cd ${WRKSRC}/libxmms && ${LOCALBASE}/bin/autoconf-${AUTOCONF_VERSION}

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/xmms
	cd ${WRKSRC} && ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/doc/xmms

.include <bsd.port.mk>
