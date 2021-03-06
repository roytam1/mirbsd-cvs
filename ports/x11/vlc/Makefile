# $MirOS: ports/x11/vlc/Makefile,v 1.6 2006/09/14 00:15:41 tg Exp $
# $OpenBSD: Makefile,v 1.11 2004/04/28 01:30:53 jolan Exp $

COMMENT=			videolan client; multimedia player

VER=		0.7.1
DISTNAME=	vlc-${VER}
PKGNAME=	${DISTNAME}-1
CATEGORIES=	x11
MASTER_SITES=	http://www.videolan.org/pub/videolan/vlc/${VER}/ \
		http://www.fr.videolan.org/pub/videolan/vlc/${VER}/

HOMEPAGE=	http://www.videolan.org/vlc/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=	Yes

MODULES=	devel/gettext graphics/png

LIB_DEPENDS=	SDL::devel/sdl \
		gtk.1.2,gdk.1.2::x11/gtk+1 \
		glib,gthread::devel/glib1 \
		id3tag.2::audio/libid3tag \
		mad.2::audio/libmad \
		ogg::audio/libogg \
		vorbis,vorbisenc::audio/libvorbis \
		dvbpsi.1.1::graphics/libdvbpsi \
		mpeg2::graphics/libmpeg2 \
		avcodec::graphics/ffmpeg \
		fribidi::devel/fribidi \
		faad::audio/faad

CONFIGURE_STYLE=gnu
CONFIGURE_ENV=	LIBS="-logg"
CONFIGURE_ARGS+=--disable-oss \
		--enable-sdl \
		--enable-mad \
		--disable-optimizations \
		--disable-vcd \
		--disable-dvd \
		--disable-cddax \
		--disable-skins2 \
		--disable-speex \
		--enable-faad


USE_CXX=	Yes

FLAVOURS=	no_dvd
FLAVOUR?=

.if ${MACHINE_ARCH} == "i386"
SED_PLIST+=	|sed -e '/^IF${MACHINE_ARCH}:/s///'
.else
SED_PLIST+=	|sed -e '/^IFi386:/d'
.endif

.if ${MACHINE_ARCH} == "powerpc"
SED_PLIST+=	|sed -e '/^IF${MACHINE_ARCH}:/s///'
.else
SED_PLIST+=	|sed -e '/^IFpowerpc:/d'
.endif

# XXX video window initialization fails without this
.if ${MACHINE_ARCH} == "sparc64"
CFLAGS+=-mhard-quad-float
.endif

.if ${FLAVOUR:L:Mno_dvd}
CONFIGURE_ARGS+=--disable-a52 --disable-dvdplay --disable-dvdread
.else
CONFIGURE_ARGS+=--enable-a52 --enable-dvdplay --enable-dvdread
LIB_DEPENDS+=	a52::audio/liba52 \
		dvdplay::devel/libdvdplay \
		dvdread::devel/libdvdread
.endif

.include <bsd.port.mk>
