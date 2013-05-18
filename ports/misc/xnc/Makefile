# $OpenBSD: Makefile,v 1.12 2003/12/26 19:34:23 naddy Exp $

COMMENT=	"filemanager for X Window"

DISTNAME=	xnc-4.4.7
DISTFILES=      ${DISTNAME}.src${EXTRACT_SUFX}
CATEGORIES=	misc x11


HOMEPAGE=	http://xnc.dubna.su

MASTER_SITES=	${HOMEPAGE}/src/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=	tiff.36::graphics/tiff
MODULES+=		graphics/png

USE_X11=	Yes
USE_CXX=	Yes
NO_REGRESS=	Yes

CONFIGURE_STYLE=	autoconf old dest

CONFIGURE_ARGS=	--with-x

XNLAUNCHFILES=	.launch.menu .xnlaunch.ini graphs.gif ives.gif kill.gif \
		map.gif netscape.gif term.gif tnet.gif

post-patch:
	@perl -pi -e 's,\@prefix\@,${PREFIX},g' ${WRKSRC}/xncdirs.h.in

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/xnc
	cd ${WRKSRC}/.xlaunch && \
	${INSTALL_DATA} ${XNLAUNCHFILES} ${PREFIX}/share/examples/xnc
	cd ${PREFIX}/bin && \
	${STRIP} iedit ives vs xjpegroot xnc xnlaunch xncloader xncsetup
	sed -e 's,^ ,,' <${PREFIX}/man/man1/xnlaunch.1 >${PREFIX}/man/cat1/xnlaunch.0
	rm -f ${PREFIX}/man/man1/xnlaunch.1

.include <bsd.port.mk>
