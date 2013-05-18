# $MirOS: ports/graphics/ffmpeg/Makefile,v 1.7 2008/10/04 19:03:10 tg Exp $
# $OpenBSD: Makefile,v 1.9 2004/04/18 00:36:22 jolan Exp $

COMMENT=	audio/video converter and streamer with bktr(4) support
DISTNAME=	ffmpeg-0.4.9-pre1
PKGNAME=	${DISTNAME:S/-pre/pre/}-0
CATEGORIES=	graphics x11
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=ffmpeg/}
# XXX needs to be changed back on next update, including configure
SV=		4.9 

HOMEPAGE=	http://ffmpeg.sourceforge.net/


# GPL
PERMIT_DISTFILES_CDROM=	"patents"
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	"patents"
PERMIT_PACKAGE_FTP=	Yes

LIB_DEPENDS=	SDL::devel/sdl \
		a52::audio/liba52 \
		mp3lame::audio/lame \
		vorbis,vorbisenc::audio/libvorbis \

NO_REGRESS=	Yes	# Possible to adapt with some work
USE_GMAKE=	Yes
USE_X11=	Yes
EXTRA_XAKE_FLAGS+=	TRUEPREFIX=${TRUEPREFIX:Q}

# It's either this or disable mmx so postprocess_template.c will build.
.if ${MACHINE_ARCH} == "i386"
CFLAGS+=-fomit-frame-pointer
.endif

CONFIGURE_STYLE=simple
CONFIGURE_ARGS+=${CONFIGURE_SHARED} \
		--cc=${_PASS_CC:T:Q} \
		--make=${MAKE_PROGRAM} \
		--extra-cflags="-I${LOCALBASE}/include" \
		--extra-ldflags="-L${LOCALBASE}/lib -L${X11BASE}/lib" \
		--disable-opts \
		--enable-pp \
		--enable-mp3lame \
		--enable-vorbis \
		--enable-a52bin \
		--disable-debug \
		--disable-vhook \
		--disable-debug \
		--enable-gpl

# bktr(4) support
.if ${MACHINE_ARCH} != "i386" && ${MACHINE_ARCH} != "powerpc"
CONFIGURE_ARGS+=--disable-v4l
.endif

post-extract:
	@cp ${FILESDIR}/grab_bsdbktr.c ${WRKSRC}/libavformat/

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/ffmpeg
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/examples/ffmpeg
	${INSTALL_DATA} ${WRKSRC}/doc/*.html ${PREFIX}/share/doc/ffmpeg
	${INSTALL_DATA} ${WRKSRC}/doc/ffserver.conf \
		${PREFIX}/share/doc/examples/ffmpeg
	${INSTALL_MAN} ${WRKSRC}/doc/*.1 ${PREFIX}/man/man1
	${INSTALL_PROGRAM} ${WRKBUILD}/ffmpeg ${PREFIX}/bin/ffmpeg
	${INSTALL_PROGRAM} ${WRKBUILD}/ffplay ${PREFIX}/bin/ffplay
	${INSTALL_PROGRAM} ${WRKBUILD}/ffserver ${PREFIX}/bin/ffserver
	${INSTALL_DATA_DIR} ${PREFIX}/include/ffmpeg
	${INSTALL_DATA_DIR} ${PREFIX}/include/postproc
	${INSTALL_DATA} ${WRKSRC}/libavcodec/{avcodec,common}.h \
		${PREFIX}/include/ffmpeg
	${INSTALL_DATA} ${WRKSRC}/libavformat/{avformat.h,avio.h,rtp.h,rtsp.h,rtspcodes.h} \
		${PREFIX}/include/ffmpeg
	${INSTALL_DATA} ${WRKBUILD}/libavcodec/libpostproc/postprocess.h \
		${PREFIX}/include/postproc
	${INSTALL_DATA} ${WRKBUILD}/libavcodec/libavcodec.a \
		${WRKBUILD}/libavformat/libavformat.a ${PREFIX}/lib
.if !defined(NO_SHARED_LIBS)
	${INSTALL_DATA} ${WRKBUILD}/libavcodec/libavcodec.so.${SV} \
		${PREFIX}/lib/libavcodec.so.${SV}
	${INSTALL_DATA} ${WRKBUILD}/libavformat/libavformat.so.${SV} \
		${PREFIX}/lib/libavformat.so.${SV}
.endif
	
.include <bsd.port.mk>
