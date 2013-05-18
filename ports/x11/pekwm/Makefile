# $MirOS: ports/x11/pekwm/Makefile,v 1.1.7.1 2005/03/18 16:00:49 tg Exp $
# $OpenBSD: Makefile,v 1.4 2004/02/25 02:35:18 naddy Exp $

COMMENT=			aewm++ based pretty themable window manager
VERSION=	0.1.3
DISTNAME=	pekwm-${VERSION}
CATEGORIES=	x11
HOMEPAGE=	http://pekwm.pekdon.net/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}files/source/

USE_X11= 		Yes
USE_CXX=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE=	simple
CONFIGURE_ARGS+=	--prefix=${LOCALBASE} \
			--enable-shape \
			--enable-menus \
			--enable-keygrabber \
		        --enable-harbour \
			--disable-pcre \
			--disable-xinerama \
			--disable-debug 

NO_REGRESS=		Yes

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/pekwm
	cd ${WRKBUILD}/src && ${MAKE_PROGRAM} install
	cd ${WRKBUILD}/docs && ${MAKE_PROGRAM} install
	cd ${WRKBUILD}/data && ${MAKE_PROGRAM} install \
	    SYSCONFDIR=${TRUEPREFIX}/share/examples/pekwm
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/pekwm

.include <bsd.port.mk>
