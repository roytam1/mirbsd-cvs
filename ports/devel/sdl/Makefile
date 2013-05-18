# $MirOS: ports/devel/sdl/Makefile,v 1.11 2007/04/03 19:42:11 tg Exp $
# $OpenBSD: Makefile,v 1.32 2004/04/23 12:09:18 robert Exp $
# Uses pthreads

COMMENT=		cross-platform multimedia library
VERSION=		1.2.9
DISTNAME=		SDL-${VERSION}
PKGNAME=		sdl-${VERSION}-4
CATEGORIES=		devel
HOMEPAGE=		http://www.libsdl.org/

# GNU LGPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=		${HOMEPAGE}release/ \
			http://www.devolution.com/~slouken/SDL/release/

.include <mirports.sys.mk>

CONFIGURE_STYLE=	autogen		# and ignore ${WRKSRC}/test for now
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ENV+=		X11BASE="${X11BASE}"
.if ${MACHINE_OS} == "BSD"
CONFIGURE_ENV+=		ac_cv_header_usb_h=no
.endif
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--disable-oss \
			--disable-alsa \
			--disable-ltdl \
			--enable-dlopen \
			--enable-pthread-sem

FLAVOURS=		sun esd aa no_x11
FLAVOUR?=		sun

.if ${MACHINE_ARCH} == "i386"
BUILD_DEPENDS+=		nasm::lang/nasm
CONFIGURE_ARGS+=	--enable-nasm
.else
CONFIGURE_ARGS+=	--disable-nasm
.endif

.if ${FLAVOUR:L:Msun}
CONFIGURE_ARGS+=	--enable-openbsdaudio
.else
CONFIGURE_ARGS+=	--disable-openbsdaudio
.endif

.if ${FLAVOUR:L:Mesd}
LIB_DEPENDS+=		esd::audio/esound
CONFIGURE_ARGS+=	--enable-esd
.else
CONFIGURE_ARGS+=	--disable-esd
.endif

CONFIGURE_ARGS+=	--disable-arts

.if ${FLAVOUR:L:Maa}
LIB_DEPENDS+=		aa::graphics/aalib
CONFIGURE_ARGS+=	--enable-video-aalib
.else
CONFIGURE_ARGS+=	--disable-video-aalib
.endif

.if ${FLAVOUR:L:Mno_x11}
CONFIGURE_ARGS+=	--without-x \
			--disable-video-x11
.else
USE_X11=		Yes
.endif

NO_REGRESS=		Yes

.include <bsd.port.mk>
