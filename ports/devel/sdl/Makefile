# $MirOS: ports/devel/sdl/Makefile,v 1.5 2005/12/28 16:37:57 tg Exp $
# $OpenBSD: Makefile,v 1.32 2004/04/23 12:09:18 robert Exp $
# Uses pthreads

COMMENT=		"cross-platform multimedia library"
VERSION=		1.2.9
DISTNAME=		SDL-${VERSION}
PKGNAME=		sdl-${VERSION}-1
CATEGORIES=		devel
HOMEPAGE=		http://www.libsdl.org/

# GNU LGPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=		${HOMEPAGE}release/ \
			http://www.devolution.com/~slouken/SDL/release/

CONFIGURE_STYLE=	autogen		# and ignore ${WRKSRC}/test for now
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
CONFIGURE_ENV+=		X11BASE="${X11BASE}"
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--disable-oss \
			--disable-ltdl \
			--enable-dlopen \
			--enable-pthread-sem

FLAVORS=		sun esd arts aa no_x11
FLAVOR?=		sun

.if ${MACHINE_ARCH} == "i386"
BUILD_DEPENDS+=		nasm::lang/nasm
CONFIGURE_ARGS+=	--enable-nasm
.else
CONFIGURE_ARGS+=	--disable-nasm
.endif

.if ${FLAVOR:L:Msun}
CONFIGURE_ARGS+=	--enable-openbsdaudio
.else
CONFIGURE_ARGS+=	--disable-openbsdaudio
.endif

.if ${FLAVOR:L:Mesd}
LIB_DEPENDS+=		esd::audio/esound
CONFIGURE_ARGS+=	--enable-esd
.else
CONFIGURE_ARGS+=	--disable-esd
.endif

.if ${FLAVOR:L:Marts}
LIB_DEPENDS+=		artsc::x11/kde/arts3
CONFIGURE_ARGS+=	--enable-arts
.else
CONFIGURE_ARGS+=	--disable-arts
.endif

.if ${FLAVOR:L:Maa}
LIB_DEPENDS+=		aa::graphics/aalib
CONFIGURE_ARGS+=	--enable-video-aalib
.else
CONFIGURE_ARGS+=	--disable-video-aalib
.endif

.if ${FLAVOR:L:Mno_x11}
CONFIGURE_ARGS+=	--without-x \
			--disable-video-x11
.else
USE_X11=		Yes
.endif

NO_REGRESS=		Yes

.include <bsd.port.mk>
