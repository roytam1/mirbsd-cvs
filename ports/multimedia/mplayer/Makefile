# $MirOS: ports/multimedia/mplayer/Makefile,v 1.13 2006/02/09 11:12:11 tg Exp $
# $OpenBSD: Makefile,v 1.83 2005/05/09 12:24:38 biorn Exp $

# May not be hard to add more.
# <mira> waldi: in mplayer sind mehr LP64 bugs pro KB source drin als in pine
ONLY_FOR_PLATFORM=	*:*:i386 *:*:powerpc OpenBSD:*:arm OpenBSD:*:amd64 #XXX

COMMENT=		"Movie player supporting MPEG, DivX, AVI, ASF, MOV & more"
DISTNAME=		MPlayer-1.0pre7
DIST_SUBDIR=		mplayer
PKGNAME=		${DISTNAME:L}-3
CATEGORIES=		x11 multimedia
EXTRACT_SUFX=		.tar.bz2
HOMEPAGE=		http://www.mplayerhq.hu/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>

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

MODULES=	converters/libiconv graphics/png

LIB_DEPENDS=	jpeg::graphics/jpeg \
		mp3lame::audio/lame,no_x11 \
		theora::multimedia/libtheora \
		cdda_paranoia,cdda_interface:cdparanoia->=3.a9.8:audio/cdparanoia

CONFDIR=	${SYSCONFDIR}/mplayer
SUBST_VARS=	CONFDIR

USE_GMAKE=	Yes
CONFIGURE_STYLE=simple
CONFIGURE_ARGS+=--disable-alsa \
		--disable-runtime-cpudetection \
		--disable-gui \
		--disable-nas \
		--disable-i18n \
		--disable-libdv \
		--disable-smb \
		--enable-select \
		--enable-sunaudio \
		--disable-vidix \
		--enable-vorbis \
		--enable-theora \
		--enable-menu \
		--enable-iconv \
		--disable-vesa \
		--disable-directfb \
		--enable-cdparanoia \
		--with-extraincdir=${LOCALBASE}/include/libpng:${LOCALBASE}/include \
		--with-extralibdir=${LOCALBASE}/lib \
		--prefix=${PREFIX:Q} \
		--cc=${CC:Q} \
		--confdir=${CONFDIR}
# disable OSS audio if no TV needed
CONFIGURE_ARGS+=--enable-ossaudio \
		--enable-tv-bsdbt848
CONFIGURE_ENV+=	TMPDIR=${WRKBUILD}

.if ${MACHINE_ARCH:Mi386}
CONFIGURE_ARGS+=--enable-runtime-cpudetection
.endif

.if ${MACHINE_ARCH:Mpowerpc}
CONFIGURE_ARGS+=--disable-altivec
.endif

FLAVORS=	arts esd sdl ggi debug mad no_x11 aa \
		no_live no_ungif no_lzo caca
FLAVOR?=

.if ${MACHINE_ARCH:Marm}
CONFIGURE_ARGS+=--disable-mp3lib
FLAVOR+=	mad
.endif

.if ${FLAVOR:L:Mno_lzo}
CONFIGURE_ARGS+=--disable-liblzo
.else
LIB_DEPENDS+=	lzo2:lzo->=2.*:archivers/lzo
CPPFLAGS+=	-I${LOCALBASE}/include/lzo
CONFIGURE_ARGS+=--enable-liblzo
.endif

.if ${FLAVOR:L:Mno_live}
CONFIGURE_ARGS+=--disable-live
.else
USE_CXX=	Yes
BUILD_DEPENDS+=	livestream::multimedia/livestream
CONFIGURE_ARGS+=--enable-live \
		--with-livelibdir=${PREFIX}/lib/live
.endif

.if ${FLAVOR:L:Mno_ungif}
CONFIGURE_ARGS+=--disable-gif
.else
USE_CXX=	Yes
LIB_DEPENDS+=	ungif,gif::graphics/libungif
# don't --enable-gif here!
.endif

.if ${FLAVOR:L:Marts}
CONFIGURE_ARGS+=--enable-arts
LIB_DEPENDS+=	artsc::x11/kde/arts
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
		--disable-x11 \
		--disable-fontconfig \
		--disable-freetype
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

.if ${MACHINE_ARCH:Mi386}
RUN_DEPENDS+=	:win32-codecs-*:multimedia/win32-codecs
CONFIGURE_ARGS+=--with-win32libdir=${LOCALBASE}/lib/codecs \
		--enable-qtx \
		--enable-real \
		--enable-dshow \
		--with-reallibdir=${LOCALBASE}/lib/codecs
.else
CONFIGURE_ARGS+=--disable-win32 \
		--disable-qtx \
		--disable-dshow \
		--disable-real
.endif

.if ${FLAVOR:L:Maa}
CONFIGURE_ARGS+=--enable-aa
.  if ${FLAVOR:L:Mno_x11}
LIB_DEPENDS+=	aa::graphics/aalib,no_x11
.  else
LIB_DEPENDS+=	aa::graphics/aalib
.  endif
.else
CONFIGURE_ARGS+=--disable-aa
.endif

.if ${FLAVOR:L:Mcaca}
CONFIGURE_ARGS+=--enable-caca
.  if ${FLAVOR:L:Mno_x11}
BUILD_DEPENDS+=	::graphics/libcaca,no_x11
.  else
BUILD_DEPENDS+=	::graphics/libcaca
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
