# $MirOS: ports/multimedia/mjpegtools/Makefile,v 1.3 2006/02/09 09:36:06 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/07/09 11:58:39 sturm Exp $

COMMENT=		"tools to edit/modify/encode video streams"

DISTNAME=		mjpegtools-1.6.2
CATEGORIES=		multimedia

HOMEPAGE=		http://mjpeg.sourceforge.net/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=mjpeg/}

LIB_DEPENDS=		SDL.2:sdl-*-!no_x11:devel/sdl \
			dv.4::multimedia/libdv \
			gdk.1.2,gtk.1.2::x11/gtk+1 \
			jpeg.62::graphics/jpeg
MODULES+=		devel/pkgconfig graphics/png

AUTOCONF_NEW=	Yes
CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--with-x --enable-xfree-ext \
			--with-dv=${LOCALBASE} --with-dv-yv12 \
			--disable-zalpha

FLAVORS=		quicktime optimized
FLAVOR?=

.if ${FLAVOR:L:Moptimized}
CONFIGURE_ARGS+=	--enable-simd-accel
.  if ${MACHINE_ARCH} == "i386"
BUILD_DEPENDS+=		::devel/nasm
CONFIGURE_ARGS+=	--enable-cmov-extension
.  endif
.else
CONFIGURE_ARGS+=	--disable-cmov-extension \
			--disable-simd-accel
.endif

.if ${FLAVOR:L:Mquicktime}
LIB_DEPENDS+=		quicktime.0::multimedia/libquicktime
CONFIGURE_ARGS+=	--with-quicktime
.else
CONFIGURE_ARGS+=	--without-quicktime
.endif

post-install:
	${INSTALL_DATA} ${WRKBUILD}/utils/libmjpegutils_pic.a ${PREFIX}/lib

NO_REGRESS=		Yes

.include <bsd.port.mk>
