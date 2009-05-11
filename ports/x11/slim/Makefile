# $MirOS$
# $OpenBSD: Makefile,v 1.5 2008/11/05 13:36:41 pea Exp $

COMMENT=		simple login manager

DISTNAME=		slim-1.3.1
CATEGORIES=		x11
HOMEPAGE=		http://slim.berlios.de/
MASTER_SITES=		${MASTER_SITE_BERLIOS:=slim/}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
USE_CXX=		Yes
NO_REGRESS=		Yes
LIB_DEPENDS=		jpeg::graphics/jpeg \
			png::graphics/png

MAKE_FILE=		${FILESDIR}/Makefile.MirPorts
EXTRA_XAKE_FLAGS=	SYSCONFDIR=${SYSCONFDIR}
SUBST_VARS+=		LOCALBASE X11BASE

pre-configure:
	${SUBST_CMD} ${WRKSRC}/slim.1 ${WRKSRC}/slim.conf

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/slim
	${INSTALL_DATA} ${FILESDIR}/README.MirPorts \
		${PREFIX}/share/doc/slim
	${SUBST_CMD} ${PREFIX}/share/doc/slim/README.MirPorts

.include <bsd.port.mk>
