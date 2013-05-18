# $MirOS: ports/graphics/cqcam/Makefile,v 1.4 2005/04/11 15:55:34 tg Exp $
# $OpenBSD: Makefile,v 1.6 2002/12/29 20:08:46 fgsch Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

DISTNAME=	cqcam-0.91
CATEGORIES=	graphics

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

COMMENT=	"color QuickCam control program"
HOMEPAGE=	http://www.cs.duke.edu/~reynolds/cqcam/
MASTER_SITES=	${HOMEPAGE} \
		ftp://rt.fm/pub/cqcam/

USE_X11=	Yes
USE_CXX=	Yes
LIB_DEPENDS=	jpeg.62::graphics/jpeg

CONFIGURE_STYLE= gnu dest
CONFIGURE_ARGS=	--enable-jpeg --enable-asm

NO_REGRESS=	Yes

FLAVORS=	no_x11
FLAVOR?=	

.if ${FLAVOR:L:Mno_x11}
EXTRA_XAKE_FLAGS=	CLIENTS="cli webcam"
.else
USE_X11=	Yes
LIB_DEPENDS+=	gtk.1,gdk.1::x11/gtk+1
LIB_DEPENDS+=	xview,olgx::x11/xview/lib
#BUILD_DEPENDS=	wish8.3::x11/tk/8.3
CONFIGURE_ARGS+= --with-gtk-prefix=${LOCALBASE} 
EXTRA_XAKE_FLAGS=	CLIENTS="cli gtkfe webcam xfe"
.endif

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/cqcam
	${INSTALL_DATA} ${WRKSRC}/docs/README.webcam \
		${PREFIX}/share/doc/cqcam/README.webcam
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/cqcam
	${INSTALL_DATA} ${WRKSRC}/.cqcrc \
		${PREFIX}/share/examples/cqcam/dot.cqcrc
	${INSTALL_DATA} ${WRKSRC}/webcam/nph-webcam \
		${PREFIX}/share/examples/cqcam/nph-webcam

.include <bsd.port.mk>
