# $MirOS: ports/multimedia/mplayer/Makefile,v 1.22 2009/05/24 19:52:54 tg Exp $
# $OpenBSD: Makefile,v 1.83 2005/05/09 12:24:38 biorn Exp $

# May not be hard to add more.
# <mira> waldi: in mplayer sind mehr LP64 bugs pro KB source drin als in pine
ONLY_FOR_PLATFORM=	*:*:i386 *:*:powerpc OpenBSD:*:arm OpenBSD:*:amd64 #XXX

COMMENT=		Movie player supporting MPEG, DivX, AVI, ASF, MOV & more
DISTNAME=		MPlayer-1.0pre7
DIST_SUBDIR=		mplayer
PKGNAME=		${DISTNAME:L}-4
CATEGORIES=		x11 multimedia
EXTRACT_SUFX=		.tar.bz2
HOMEPAGE=		http://www.mplayerhq.hu/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

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
		--prefix=${PREFIX:Q} \
		--cc=${_PASS_CC:T:Q} \
		--confdir=${CONFDIR}
# disable OSS audio if no TV needed
CONFIGURE_ARGS+=--enable-ossaudio \
		--enable-tv-bsdbt848
CONFIGURE_ENV+=	TMPDIR=${WRKBUILD}

CF_INCDIR:=	${LOCALBASE:Q}/include/libpng:${LOCALBASE:Q}/include
CF_LIBDIR:=	${LOCALBASE:Q}/lib

.if ${MACHINE_ARCH:Mi386}
CONFIGURE_ARGS+=--enable-runtime-cpudetection
.endif

.if ${MACHINE_ARCH:Mpowerpc}
CONFIGURE_ARGS+=--disable-altivec
.endif

FLAVOURS=	esd sdl ggi debug mad no_x11 aa \
		no_live no_ungif no_lzo caca
FLAVOUR?=

.if ${MACHINE_ARCH:Marm}
CONFIGURE_ARGS+=--disable-mp3lib
FLAVOUR+=	mad
.endif

.if ${FLAVOUR:L:Mno_lzo}
CONFIGURE_ARGS+=--disable-liblzo
.else
LIB_DEPENDS+=	lzo2:lzo->=2.*:archivers/lzo
CF_INCDIR:=	${LOCALBASE:Q}/include/lzo:${CF_INCDIR}
CONFIGURE_ARGS+=--enable-liblzo
.endif

.if ${FLAVOUR:L:Mno_live}
CONFIGURE_ARGS+=--disable-live
.else
USE_CXX=	Yes
BUILD_DEPENDS+=	livestream::multimedia/livestream
CONFIGURE_ARGS+=--enable-live \
		--with-livelibdir=${PREFIX}/lib/live
.endif

.if ${FLAVOUR:L:Mno_ungif}
CONFIGURE_ARGS+=--disable-gif
.else
USE_CXX=	Yes
LIB_DEPENDS+=	ungif,gif::graphics/libungif
# don't --enable-gif here!
.endif

CONFIGURE_ARGS+=--disable-arts

.if ${FLAVOUR:L:Mesd}
CONFIGURE_ARGS+=--enable-esd
LIB_DEPENDS+=	esd::audio/esound
.else
CONFIGURE_ARGS+=--disable-esd
.endif

.if ${FLAVOUR:L:Mno_x11}
.  if ${FLAVOUR:L:Msdl} || ${FLAVOUR:L:Mggi} || ${FLAVOUR:L:Mmad}
ERRORS+=	"Fatal: nonsense combination of flavours"
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

.if ${FLAVOUR:L:Msdl}
CONFIGURE_ARGS+=--enable-sdl \
		--with-sdl-config=${LOCALBASE}/bin/sdl-config
LIB_DEPENDS+=	SDL:sdl-1.2.4p1,>=1.2.5:devel/sdl
.else
CONFIGURE_ARGS+=--disable-sdl
.endif

.if ${FLAVOUR:L:Mggi}
CONFIGURE_ARGS+=--enable-ggi
LIB_DEPENDS+=	ggi::graphics/ggi
.else
CONFIGURE_ARGS+=--disable-ggi
.endif

.if ${FLAVOUR:L:Mdebug}
CONFIGURE_ARGS+=--enable-debug=3
.endif

.if ${FLAVOUR:L:Mmad}
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

.if ${FLAVOUR:L:Maa}
CONFIGURE_ARGS+=--enable-aa
.  if ${FLAVOUR:L:Mno_x11}
LIB_DEPENDS+=	aa::graphics/aalib,no_x11
.  else
LIB_DEPENDS+=	aa::graphics/aalib
.  endif
.else
CONFIGURE_ARGS+=--disable-aa
.endif

.if ${FLAVOUR:L:Mcaca}
CONFIGURE_ARGS+=--enable-caca
.  if ${FLAVOUR:L:Mno_x11}
BUILD_DEPENDS+=	::graphics/libcaca,no_x11
.  else
BUILD_DEPENDS+=	::graphics/libcaca
.  endif
.else
CONFIGURE_ARGS+=--disable-caca
.endif

.if ${USE_CXX:L} != "yes"
EXTRA_XAKE_FLAGS+=	CXX=${_PASS_CXX:T:Q}
.endif

CONFIGURE_ARGS+=	--with-extraincdir=${CF_INCDIR} \
			--with-extralibdir=${CF_LIBDIR}

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
