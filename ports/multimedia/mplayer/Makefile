# $MirOS$
# $OpenBSD: Makefile,v 1.69 2004/05/06 07:27:36 biorn Exp $

# May not be hard to add more.
ONLY_FOR_ARCHS=		amd64 i386 macppc

# <mira> waldi: in mplayer sind mehr LP64 bugs pro KB source drin als in pine
NOT_FOR_ARCHS=		${LP64_ARCHS}

COMMENT=		"Movie player supporting MPEG, DivX, AVI, ASF, MOV & more"
DISTNAME=		MPlayer-1.0pre5try2
DIST_SUBDIR=		mplayer
PKGNAME=		${DISTNAME:L}
CATEGORIES=		x11 multimedia
EXTRACT_SUFX=		.tar.bz2
HOMEPAGE=		http://www.mplayerhq.hu/
RESPONSIBLE=		Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>

# GNU GPLv2
# XXX unsure of GPL-compatibility of _all_ components -tg@
PERMIT_PACKAGE_CDROM=	"patents"
PERMIT_PACKAGE_FTP=	"different licencing of components"
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://www2.mplayerhq.hu/MPlayer/releases/
MASTER_SITES+=		http://www.mplayerhq.hu/MPlayer/releases/
MASTER_SITES+=		http://ftp.lug.udel.edu/MPlayer/releases/

.include <mirports.sys.mk>

MODULES=	converters/libiconv

LIB_DEPENDS=	png::graphics/png \
		jpeg::graphics/jpeg \
		mp3lame::audio/lame,no_x11 \
		vorbis.0,vorbisfile.1::audio/libvorbis \
		cdda_paranoia,cdda_interface:cdparanoia->=3.a9.8:audio/cdparanoia

CONFDIR=	${SYSCONFDIR}/mplayer
SUBST_VARS=	CONFDIR

USE_GMAKE=	Yes
CONFIGURE_STYLE=simple
CONFIGURE_ARGS+=--disable-alsa \
		--disable-runtime-cpudetection \
		--disable-gui \
		--disable-nas \
		--disable-liblzo \
		--disable-i18n \
		--enable-select \
		--enable-sunaudio \
		--disable-vidix \
		--enable-vorbis \
		--enable-menu \
		--enable-iconv \
		--disable-vesa \
		--disable-directfb \
		--enable-cdparanoia \
		--with-extraincdir=${LOCALBASE}/include/libpng:${LOCALBASE}/include \
		--with-extralibdir=${LOCALBASE}/lib \
		--cc="${CC}" \
		--confdir=${CONFDIR}
# disable OSS audio if no TV needed
CONFIGURE_ARGS+=--enable-ossaudio \
		--enable-tv-bsdbt848
CONFIGURE_ENV+=	TMPDIR=${WRKBUILD}

.if ${MACHINE_ARCH:Mpowerpc}
CONFIGURE_ARGS+=--disable-altivec
.endif

FLAVORS=	arts esd sdl ggi debug mad win32 no_x11 aa \
		faad no_live no_ungif mkv caca
FLAVOR?=

.if ${FLAVOR:L:Mfaad}
USE_CXX=	Yes
LIB_DEPENDS+=	faad::audio/faad
CONFIGURE_ARGS+=--enable-external-faad
.else
CONFIGURE_ARGS+=--disable-external-faad
.endif

.if ${FLAVOR:L:Mno_live}
CONFIGURE_ARGS+=--disable-live
.else
USE_CXX=	Yes
BUILD_DEPENDS+=	livestream::graphics/livestream
CONFIGURE_ARGS+=--enable-live
.endif

.if ${FLAVOR:L:Mno_ungif}
CONFIGURE_ARGS+=--disable-gif
.else
USE_CXX=	Yes
LIB_DEPENDS+=	ungif,gif::graphics/libungif
# don't --enable-gif here!
.endif

.if ${FLAVOR:L:Mmkv}
USE_CXX=	Yes
LIB_DEPENDS+=	matroska::graphics/libmatroska
CONFIGURE_ARGS+=--enable-external-matroska
.else
CONFIGURE_ARGS+=--disable-external-matroska
.endif

.if ${FLAVOR:L:Marts}
CONFIGURE_ARGS+=--enable-arts
LIB_DEPENDS+=	artsc::x11/kde/arts3
.else
CONFIGURE_ARGS+=--disable-arts
.endif

.if ${FLAVOR:L:Mesd}
CONFIGURE_ARGS+=--enable-esd
LIB_DEPENDS+=	esd::audio/esound
.else
CONFIGURE_ARGS+=--disable-esd
.endif

.if ${FLAVOR:L:Mno_x11}
.  if ${FLAVOR:L:Msdl} || ${FLAVOR:L:Mggi} || ${FLAVOR:L:Mmad}
ERRORS+=	"Fatal: nonsense combination of flavors"
.  else
CONFIGURE_ARGS+=--disable-gl \
		--disable-xv \
		--disable-x11
.  endif
.else
CONFIGURE_ARGS+=--enable-gl \
		--enable-xv \
		--enable-x11
USE_X11=	Yes
.endif

.if ${FLAVOR:L:Msdl}
CONFIGURE_ARGS+=--enable-sdl \
		--with-sdl-config=${LOCALBASE}/bin/sdl-config
LIB_DEPENDS+=	SDL:sdl-1.2.4p1,>=1.2.5:devel/sdl
.else
CONFIGURE_ARGS+=--disable-sdl
.endif

.if ${FLAVOR:L:Mggi}
CONFIGURE_ARGS+=--enable-ggi
LIB_DEPENDS+=	ggi::graphics/ggi
.else
CONFIGURE_ARGS+=--disable-ggi
.endif

.if ${FLAVOR:L:Mdebug}
CONFIGURE_ARGS+=--enable-debug=3
.endif

.if ${FLAVOR:L:Mmad}
CONFIGURE_ARGS+=--enable-mad
LIB_DEPENDS+=	mad.2::audio/libmad
.else
CONFIGURE_ARGS+=--disable-mad
.endif

.if ${FLAVOR:L:Mwin32}
ONLY_FOR_ARCHS=	i386

RUN_DEPENDS+=	:win32-codecs-*:graphics/win32-codecs
BUILD_DEPENDS+=	:win32-codecs-*:graphics/win32-codecs
CONFIGURE_ARGS+=--with-win32libdir=${LOCALBASE}/lib/win32 \
		--enable-qtx \
		--enable-real \
		--enable-dshow \
		--with-reallibdir=${LOCALBASE}/lib/win32
.else
CONFIGURE_ARGS+=--disable-win32 \
		--disable-qtx \
		--disable-dshow \
		--disable-real
.endif

.if ${FLAVOR:L:Maa}
CONFIGURE_ARGS+=--enable-aa
.  if ${FLAVOR:L:Mno_x11}
LIB_DEPENDS+=	aa.1.3::graphics/aalib,no_x11
.  else
LIB_DEPENDS+=	aa.1.3::graphics/aalib
.  endif
.else
CONFIGURE_ARGS+=--disable-aa
.endif

.if ${FLAVOR:L:Mcaca}
CONFIGURE_ARGS+=--enable-caca
.  if ${FLAVOR:L:Mno_x11}
LIB_DEPENDS+=	caca.1::graphics/libcaca,no_x11
.  else
LIB_DEPENDS+=	caca.1::graphics/libcaca
.  endif
.else
CONFIGURE_ARGS+=--disable-caca
.endif

.if ${USE_CXX:L} != "yes"
EXTRA_XAKE_FLAGS+=	CXX="${CC}"
.endif

NO_REGRESS=		Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/mplayer
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/mplayer
	cd ${WRKDIST}/etc; ${INSTALL_DATA} input.conf menu.conf codecs.conf \
	    ${PREFIX}/share/examples/mplayer/
	${INSTALL_DATA} ${WRKDIST}/etc/example.conf \
	    ${PREFIX}/share/examples/mplayer/mplayer.conf
	${INSTALL_DATA} ${WRKDIST}/DOCS/HTML/en/*.html \
	    ${PREFIX}/share/doc/mplayer/

.include <bsd.port.mk>
