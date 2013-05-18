# $MirOS: ports/x11/xglobe/Makefile,v 1.6 2008/10/04 19:03:51 tg Exp $
# $OpenBSD: Makefile,v 1.21 2003/02/25 10:34:02 espie Exp $

COMMENT=	display the Earth on X11

CATEGORIES=	x11
HOMEPAGE=	http://www.cs.unc.edu/~scheuerm/xglobe/
#MASTER_SITES=	${HOMEPAGE}
# Temporary release
MASTER_SITES=	ftp://quatramaran.ens.fr/pub/espie/
DISTNAME=	xglobe-0.5p2


# GPL, included map is free
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		x11/qt3 graphics/png
MODQT_MT=		Yes
USE_CXX=		Yes

MAKE_FLAGS=	XGLOBE_DIR=${PREFIX}

FLAVOURS=	no_map
FLAVOUR?=
.if ${FLAVOUR:L:Mno_map}
DISTFILES=	${DISTNAME}-no-map${EXTRACT_SUFX}

# Kludge install for no map around
pre-install:
	@touch ${WRKSRC}/map.bmp

post-install::
	@rm ${PREFIX}/lib/xglobe/map.bmp
.endif


MAKE_FLAGS+=	QT_INCLUDE_DIR=${MODQT_INCDIR}
MAKE_FLAGS+=	QT_LIB_DIR=${MODQT_LIBDIR}

MAKE_FLAGS+=	CPP=${_PASS_CXX:T:Q} LINK=${_PASS_CXX:T:Q}
MAKE_FLAGS+=	OPTIONS="${CXXFLAGS} -pthread -fno-exceptions -funroll-loops"
MAKE_FLAGS+=	LFLAGS='-pthread'
MAKE_FLAGS+=	LIBS='-lX11 -lqt-mt -lm'

# for linking against libpng
MAKE_FLAGS+=	'LIB_DIRS=-L$$(QT_LIB_DIR) -L$$(X11_LIB_DIR) -L$(LOCALBASE)/lib'
MAKE_FLAGS+=	COPTS='${COPTS}'

NO_REGRESS=	Yes

post-install::
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/xglobe
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/xglobe
	${INSTALL_DATA} ${WRKSRC}/README.maps ${PREFIX}/share/doc/xglobe
	${INSTALL_SCRIPT} ${FILESDIR}/getcloudmap ${PREFIX}/bin
	${INSTALL_DATA} ${FILESDIR}/OpenBSD-markers ${PREFIX}/lib/xglobe

SUPDISTFILES=	${DISTNAME}${EXTRACT_SUFX} ${DISTNAME}-no-map${EXTRACT_SUFX}

FAKE_FLAGS=	XGLOBE_DIR=${WRKINST}${PREFIX}

.include <bsd.port.mk>
