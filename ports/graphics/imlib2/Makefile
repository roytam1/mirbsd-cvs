# $MirOS$
# $OpenBSD: Makefile,v 1.1.1.1 2004/04/18 02:01:25 jolan Exp $

COMMENT=	"image manipulation library"
DISTNAME=	imlib2-1.1.0
PKGNAME=	${DISTNAME}p0
CATEGORIES=	graphics
HOMEPAGE=	http://www.enlightenment.org/pages/imlib2.html
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=enlightenment/}

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVORS=	no_cxx
FLAVOR?=	no_cxx

USE_X11=	Yes

BUILD_DEPENDS=	:pkgconfig-*:devel/pkgconfig

LIB_DEPENDS+=	ltdl.4::devel/libltdl \
		png.2::graphics/png \
		tiff.35::graphics/tiff

SEPARATE_BUILD=		concurrent
CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

.include <mirports.sys.mk>

.if ${MACHINE_ARCH} == "i386"
CONFIGURE_ARGS+=	--enable-mmx
.endif

.if ${FLAVOR:L:Mno_cxx}
CONFIGURE_ARGS+=	--disable-gif
.else
LIB_DEPENDS+=		ungif.5::graphics/libungif
USE_CXX=		Yes
.  if ${NO_SHARED_LIBS:L} != "no"
ERRORS+=		"Fatal: Must use no_ungif flavour if no shared libs."
.  endif
.endif

CPPFLAGS+=		-I${LOCALBASE}/include/libpng

.include <bsd.port.mk>
