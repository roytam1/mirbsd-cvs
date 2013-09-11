# $MirOS$
# $OpenBSD: Makefile,v 1.42 2013/04/29 12:54:00 sthen Exp $

COMMENT=		graphic library, pdf parser, viewer and utilities

VSN=			1.3
DISTNAME=		mupdf-${VSN}-source
PKGNAME=		mupdf-${VSN}-${DASH_VER}
CATEGORIES=		textproc x11
HOMEPAGE=		http://mupdf.com/

# code: Affero v3 (UGH!)
# font maps: Adobe (redist ok, see headers).
# droid font: Apache.
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

# http://git.ghostscript.com/?p=mupdf.git;a=summary
MASTER_SITES=		${HOMEPAGE}download/ \
			${HOMEPAGE}download/archive/

#RUN_DEPENDS+=		devel/desktop-file-utils
LIB_DEPENDS+=		jbig2dec::graphics/jbig2dec
LIB_DEPENDS+=		jpeg::graphics/jpeg
LIB_DEPENDS+=		openjp2:openjpeg->=2.0:graphics/openjpeg

USE_GMAKE=		Yes
USE_X11=		Yes
NO_REGRESS=		Yes

.if ${MACHINE_ARCH} == "hppa"
CFLAGS+=		-ffunction-sections
.endif

MAKE_ENV+=		build= verbose=1 mirports=yes
EXTRA_FAKE_FLAGS+=	prefix=${PREFIX} mandir=${PREFIX}/man

pre-configure:
	cp ${WRKSRC}/platform/debian/mupdf.pc{,.subst}
	${SUBST_CMD} ${WRKSRC}/platform/debian/mupdf.pc.subst
	rm -rf ${WRKSRC}/thirdparty

post-install:
	mv ${PREFIX}/bin/mupdf{-x11,}
	find ${PREFIX}/{include,lib,man,share/doc/mupdf} -type f -print0 | \
	    xargs -0 chmod a-x
	${INSTALL_DATA_DIR} ${PREFIX}/share/applications/ \
	    ${PREFIX}/share/application-registry/ ${PREFIX}/share/pixmaps \
	    ${PREFIX}/libdata/pkgconfig/
	${INSTALL_DATA} ${WRKSRC}/platform/debian/mupdf.xpm ${PREFIX}/share/pixmaps/
	${INSTALL_DATA} ${WRKSRC}/platform/debian/mupdf.applications \
	    ${PREFIX}/share/application-registry/
	${INSTALL_DATA} ${WRKSRC}/platform/debian/mupdf.desktop \
	    ${PREFIX}/share/applications/
	${INSTALL_DATA} ${WRKSRC}/platform/debian/mupdf.pc.subst \
	    ${PREFIX}/libdata/pkgconfig/mupdf.pc

.include <bsd.port.mk>
