# $MirOS: ports/audio/bmp/Makefile,v 1.3 2005/07/07 21:17:12 bsiegert Exp $
# $OpenBSD: Makefile,v 1.3 2005/01/02 18:57:26 alek Exp $

COMMENT=	"gtk+2 media player based on XMMS"
COMMENT-mp3=	"MP3 input plugin for bmp"
COMMENT-vorbis=	"Ogg Vorbis input plugin for bmp"
V=		0.9.7
DISTNAME=	bmp-$V
PKGNAME=	bmp-$V-1
PKGNAME-mp3=	bmp-mp3-$V-1
PKGNAME-vorbis=	bmp-vorbis-$V-1
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

LIB_DEPENDS=	gdk_pixbuf-2.0.400.3,gdk-x11-2.0.400.3::x11/gtk+ \
		glib-2.0.400.2,gthread-2.0.400.2::devel/glib

MULTI_PACKAGES=
PSEUDO_FLAVORS=	no_mp3 no_vorbis
FLAVOR?=

.if !${FLAVOR:L:Mno_mp3}
MULTI_PACKAGES+=-mp3
.endif
.if !${FLAVOR:L:Mno_vorbis}
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
LIB_DEPENDS+=	esd.2.34::audio/esound \
		glade-2.0.0.4::devel/libglade \
		xml2::textproc/libxml
.endif

.if defined(PACKAGING)
. if ${SUBPACKAGE} == "-mp3"
PERMIT_DISTFILES_CDROM=	"patent issues"
PERMIT_DISTFILES_FTP=	"patent issues"
RUN_DEPENDS=	::audio/bmp
. elif ${SUBPACKAGE} == "-vorbis"
LIB_DEPENDS=	vorbisfile.4.0,vorbis::audio/libvorbis
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
