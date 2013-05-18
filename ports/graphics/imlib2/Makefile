# $MirOS: ports/graphics/imlib2/Makefile,v 1.4 2005/12/28 19:00:35 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/04/18 02:01:25 jolan Exp $

COMMENT=		"image manipulation library"
DISTNAME=		imlib2-1.2.1
CATEGORIES=		graphics
HOMEPAGE=		http://www.enlightenment.org/Libraries/Imlib2/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=enlightenment/}

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVORS=		no_cxx
FLAVOR?=

USE_X11=		Yes
MODULES+=		devel/pkgconfig
LIB_DEPENDS+=		png.2::graphics/png \
			tiff.35::graphics/tiff

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

.include <mirports.sys.mk>

.if ${MACHINE_ARCH} == "i386"
CONFIGURE_ARGS+=	--enable-mmx
.endif

.if ${FLAVOR:L:Mno_cxx}
CONFIGURE_ARGS+=	--disable-gif
.else
LIB_DEPENDS+=		ungif::graphics/libungif
USE_CXX=		Yes
.  if ${NO_SHARED_LIBS:L} != "no"
ERRORS+=		"Fatal: Must use no_cxx flavour if no shared libs."
.  endif
.endif

CPPFLAGS+=		-I${LOCALBASE}/include/libpng

post-extract:
	cp ${FILESDIR}/round.c ${WRKSRC}/src/lib/

.include <bsd.port.mk>
