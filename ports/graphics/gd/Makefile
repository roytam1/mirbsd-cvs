# $MirOS: ports/graphics/gd/Makefile,v 1.4 2008/10/04 19:03:10 tg Exp $
# $OpenBSD: Makefile,v 1.37 2003/04/19 13:30:47 espie Exp $
# $FreeBSD: Makefile,v 1.5 1998/06/25 03:13:16 vanilla Exp $

# XXX what about X11 (freetype2 and Xpm are in base-X; probably make flavours)

COMMENT=			graphics library for fast image creation
DISTNAME=	gd-1.8.4
CATEGORIES=	graphics
MASTER_SITES=	http://www.boutell.com/gd/http/ \
		ftp://ftp.boutell.com/pub/boutell/gd/
HOMEPAGE=	http://www.boutell.com/gd/
LIB_DEPENDS=	jpeg.62::graphics/jpeg
MODULES+=	graphics/png print/freetype

# MIT-like, badly worded
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CPPFLAGS+=	-DHAVE_LIBJPEG -DHAVE_LIBTTF -DHAVE_LIBPNG
MAKE_FLAGS+=	COMPILER=${_PASS_CC:T:Q} prefix="${PREFIX}" \
		INCLUDEDIRS="-I. -I${LOCALBASE}/include/libpng -I${LOCALBASE}/include/freetype1/freetype -I${LOCALBASE}/include" \
		LIBS="-lgd -lm -lpng -lz -ljpeg -lttf" \
		LIBDIRS="-L. -L${LOCALBASE}/lib"
FAKE_FLAGS=	${MAKE_FLAGS} DESTDIR="${WRKINST}"

NO_REGRESS=	Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/gd
	${INSTALL_DATA} ${WRKSRC}/index.html \
	    ${PREFIX}/share/examples/gd/index.htm
	${INSTALL_DATA} ${WRKSRC}/demoin.png ${PREFIX}/share/examples/gd
	${INSTALL_DATA} ${WRKSRC}/demoout.png ${PREFIX}/share/examples/gd

.include <bsd.port.mk>

.if defined(NO_SHARED_LIBS) && ${NO_SHARED_LIBS:L} == "yes"
MAKE_ENV+=	NO_SHARED_LIBS=Yes
.endif
