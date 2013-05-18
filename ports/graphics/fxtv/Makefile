# $MirOS: ports/graphics/fxtv/Makefile,v 1.5 2006/02/09 11:11:45 tg Exp $
# $OpenBSD: Makefile,v 1.29 2003/08/04 12:33:33 espie Exp $

ONLY_FOR_PLATFORM=	*:*:i386 *:*:macppc

COMMENT=			Display and capture for Brooktree-based cards
DISTNAME=	fxtv-1.03
PKGNAME=	${DISTNAME}-1

CATEGORIES=	graphics
HOMEPAGE=	http://people.freebsd.org/~rhh/fxtv/
EXTRACT_SUFX=	.tgz

MASTER_SITES=	${HOMEPAGE} \
		http://mirror.csoft.org/fxtv/

LIB_DEPENDS=	tiff.35::graphics/tiff \
		jpeg.62::graphics/jpeg \
		Xaw3d.6.1::x11/Xaw3d

RUN_DEPENDS=	:sox->=12.12:audio/sox \
		:mpg321-*:audio/mpg321 \
		:mp3encode-*:audio/mp3encode \
		:mpeg_encode->=1.5:graphics/mpeg_encode \
		:mplex->=1.1:graphics/mplex


# BSD license
PERMIT_PACKAGE_CDROM=	"Runtime dependencies have patents"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=	Yes
NO_REGRESS=	Yes

pre-build:
	cp ${FILESDIR}/Makefile ${WRKSRC}
	@cd ${WRKSRC} && \
	    perl -pi -e 's|%%LOCALBASE%%|${LOCALBASE}|g' \
	    fxtv_cnvt.sh app_rsrc.h Fxtv

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/fxtv
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/fxtv
	${INSTALL_DATA_DIR} ${PREFIX}/share/fxtv
	${INSTALL_DATA_DIR} ${PREFIX}/share/fxtv/bitmaps
	${INSTALL_DATA} ${WRKSRC}/fxtv_cnvt.sh ${PREFIX}/share/fxtv
	${INSTALL_DATA} ${WRKSRC}/bitmaps/* ${PREFIX}/share/fxtv/bitmaps
	${INSTALL_DATA} ${WRKSRC}/Fxtv ${PREFIX}/lib/X11/app-defaults/Fxtv

.include <bsd.port.mk>
