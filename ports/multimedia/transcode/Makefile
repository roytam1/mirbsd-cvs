# $MirOS: ports/multimedia/transcode/Makefile,v 1.5 2006/06/03 16:02:40 bsiegert Exp $
# $OpenBSD: Makefile,v 1.2 2004/06/24 19:27:00 sturm Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			video stream processing tools
COMMENT-dv=			transcode plugins utilizing libdv
COMMENT-mjpegtools=			transcode plugins utilizing mjpegtools
COMMENT-xvidcore=			transcode plugins utilizing xvidcore

VERSION=		0.6.12
DASH_VER=		-1
DISTNAME=		transcode-${VERSION}
PKGNAME=		${DISTNAME}${DASH_VER}
PKGNAME-dv=		transcode-dv-${VERSION}${DASH_VER}
PKGNAME-mjpegtools=	transcode-mjpegtools-${VERSION}${DASH_VER}
PKGNAME-xvidcore=	transcode-xvidcore-${VERSION}${DASH_VER}

CATEGORIES=	multimedia graphics audio
HOMEPAGE=	http://zebra.fh-weingarten.de/~transcode/
MASTER_SITES=	http://zebra.fh-weingarten.de/~transcode/pre/

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.if ${MACHINE} == "i386"
BUILD_DEPENDS+=		::lang/nasm
SED_PLIST+=		|sed -e '/^%%i386%%/r${PKGDIR}/PFRAG.i386' -e '//d'
.else
SED_PLIST+=		|sed -e '/^%%i386%%/d'
.endif

PSEUDO_FLAVORS=         no_dv no_mjpegtools no_xvidcore
FLAVOR?=

MULTI_PACKAGES=
.if !${FLAVOR:L:Mno_dv}
MULTI_PACKAGES+=        -dv
.endif
.if !${FLAVOR:L:Mno_mjpegtools}
MULTI_PACKAGES+=        -mjpegtools
.endif
.if !${FLAVOR:L:Mno_xvidcore}
MULTI_PACKAGES+=        -xvidcore
.endif

SUBPACKAGE?=

LIB_DEPENDS+=	SDL.2::devel/sdl \
		a52.0::audio/liba52 \
		dvdread.3::devel/libdvdread \
		jpeg.62::graphics/jpeg \
		mp3lame.0::audio/lame \
		ogg.5::audio/libogg \
		vorbis.3,vorbisfile.4::audio/libvorbis \
		xml2.2.6::textproc/libxml

USE_CXX=	Yes
CONFIGURE_STYLE=autoconf
AUTOCONF_NEW=	Yes
CONFIGURE_ENV+=	LIBFAME_CONFIG="no"
CONFIGURE_ARGS+=${CONFIGURE_SHARED} \
		--enable-liba52 \
		--with-ogg --with-vorbis \
		--enable-text \
		--disable-altivec --disable-mmx --disable-sse \
		--disable-v4l \
		--with-avifile-mods=no \
		--with-magick-mods=no \
		--without-libfame \
		--without-libmpeg3 \
		--without-lzo \
		--without-openqt \
		--without-pvm3 \
		--without-qt \
		--without-theora

.if ${FLAVOR:L:Mno_dv}
CONFIGURE_ARGS+=        --without-dv
.else
CONFIGURE_ARGS+=        --with-dv
.endif

.if ${FLAVOR:L:Mno_mjpeg}
CONFIGURE_ARGS+=        --disable-mjpeg
.else
CONFIGURE_ARGS+=        --enable-mjpeg
.endif

.if ${FLAVOR:L:Mno_xvidcore}
CONFIGURE_ARGS+=        --without-xvidcore
.else
CONFIGURE_ARGS+=        --with-default-xvid=xvid4
.endif

.if defined(PACKAGING)
.  if ${SUBPACKAGE} == "-dv"
RUN_DEPENDS+=		::graphics/transcode \
			::multimedia/libdv
.  elif ${SUBPACKAGE} == "-mjpegtools"
RUN_DEPENDS+=		::graphics/transcode \
			::multimedia/mjpegtools
.  elif ${SUBPACKAGE} == "-xvidcore"
RUN_DEPENDS+=		::graphics/transcode \
			::multimedia/xvidcore
.  else
RUN_DEPENDS+=		::graphics/ffmpeg \
			::audio/sox
.  endif
.else
.  if ${MULTI_PACKAGES:M-dv}
LIB_DEPENDS+=		dv.4::multimedia/libdv
.  endif
.  if ${MULTI_PACKAGES:M-mjpegtools}
LIB_DEPENDS+=		mjpegutils.2::multimedia/mjpegtools
.  endif
.  if ${MULTI_PACKAGES:M-xvidcore}
LIB_DEPENDS+=		xvidcore.4::multimedia/xvidcore
.  endif
.endif

.include <bsd.port.mk>
