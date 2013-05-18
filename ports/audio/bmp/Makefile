# $MirOS: ports/audio/bmp/Makefile,v 1.7 2009/08/15 20:45:17 bsiegert Exp $
# $OpenBSD: Makefile,v 1.3 2005/01/02 18:57:26 alek Exp $

COMMENT=			gtk+2 media player based on XMMS
COMMENT-mp3=			MP3 input plugin for bmp
COMMENT-vorbis=			Ogg Vorbis input plugin for bmp
VSN=			0.9.7
DASH_VER=		1
DISTNAME=		bmp-${VSN}
PKGNAME=		bmp-${VSN}-${DASH_VER}
PKGNAME-mp3=		bmp-mp3-${VSN}-${DASH_VER}
PKGNAME-vorbis=		bmp-vorbis-${VSN}-${DASH_VER}
CATEGORIES=	audio
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=beepmp/}

HOMEPAGE=	http://www.sosdg.org/~larne/w/BMP_Homepage

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

USE_X11=	Yes

MODULES=	devel/gettext devel/pkgconfig

LIB_DEPENDS=	gdk_pixbuf-2.0.0.0,gdk-x11-2.0.0.0::x11/gtk+

MULTI_PACKAGES=
PSEUDO_FLAVOURS=	no_mp3 no_vorbis
FLAVOUR?=

.if !${FLAVOUR:L:Mno_mp3}
MULTI_PACKAGES+=-mp3
.endif
.if !${FLAVOUR:L:Mno_vorbis}
MULTI_PACKAGES+=-vorbis
.endif

.if !${MULTI_PACKAGES:M-mp3}
CONFIGURE_ARGS+=--disable-mp3
.endif
.if ${MULTI_PACKAGES:M-vorbis}
.  if !defined(PACKAGING)
LIB_DEPENDS+=	vorbisfile.4.0::audio/libvorbis
.  endif
.else
CONFIGURE_ARGS+=--disable-vorbis
.endif

SUBPACKAGE?=

.if $(SUBPACKAGE) != "-mp3"
LIB_DEPENDS+=	esd::audio/esound \
		glade-2.0.0.0::devel/libglade \
		xml2::textproc/libxml
.endif

.if defined(PACKAGING)
. if ${SUBPACKAGE} == "-mp3"
PERMIT_DISTFILES_CDROM=	"patent issues"
PERMIT_DISTFILES_FTP=	"patent issues"
RUN_DEPENDS=	::audio/bmp
. elif ${SUBPACKAGE} == "-vorbis"
LIB_DEPENDS=	vorbisfile,vorbis::audio/libvorbis
RUN_DEPENDS=	::audio/bmp
. endif
.endif

WRKDIST=	${WRKDIR}/bmp-0.9.7

CONFIGURE_STYLE=autoconf
AUTOCONF_NEW=	Yes
CONFIGURE_ARGS+=--disable-alsa \
		--disable-oss \
		--with-rc-path=".etc/bmp"

pre-patch:
	rm -f ${WRKSRC}/m4/libtool.m4
	touch ${WRKSRC}/m4/libtool.m4

.include <bsd.port.mk>
