# $OpenBSD: Makefile,v 1.9 2003/02/26 10:41:11 espie Exp $

COMMENT=			Qt-based 2D CAD system

PKGNAME=		${DISTNAME:S/-src//}-0
DISTNAME=		qcad-1.5.4-src
CATEGORIES=     	cad x11

HOMEPAGE=		http://www.qcad.org/


# GPL
PERMIT_PACKAGE_CDROM=	Yes 
PERMIT_PACKAGE_FTP=	Yes 
PERMIT_DISTFILES_CDROM=	Yes 
PERMIT_DISTFILES_FTP=	Yes 

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=qcad/}

MODULES=	x11/qt3
USE_CXX=	Yes
MODQT_MT=	Yes

EXTRA_MAKE_FLAGS= \
	INCPATH='-I${MODQT_INCDIR}' \
	LINK=${_PASS_CXX:T:Q} \
	LFLAGS='' \
	LIBS='-pthread -L${MODQT_LIBDIR} -L${LOCALBASE}/lib -lqt-mt -L${X11BASE}/lib -lX11' \
	AR='ar cq'
CXXFLAGS+=		-pthread -Wall -DQT_NO_DEBUG -DDATADIR=\"${PREFIX}/share\"

ALL_TARGET=		qcad
NO_REGRESS=		Yes
WRKDIST=		${WRKDIR}/${PKGNAME}

do-install:
	chmod ${DIRMODE} ${WRKSRC}/libraries/mechanical/screws/chc
	${INSTALL_PROGRAM} ${WRKBUILD}/qcad ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/qcad
	${INSTALL_DATA} ${WRKSRC}/examples/* ${PREFIX}/share/examples/qcad
.for dir in cur fonts hatches messages xpm
	${INSTALL_DATA_DIR} ${PREFIX}/share/qcad/${dir}
	${INSTALL_DATA} ${WRKSRC}/${dir}/* ${PREFIX}/share/qcad/${dir}
.endfor
	${INSTALL_DATA_DIR} ${PREFIX}/share/qcad/libraries
	cd ${WRKSRC}/libraries; cp -R * ${PREFIX}/share/qcad/libraries 
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/qcad
	cd ${WRKSRC}/doc; cp -R * ${PREFIX}/share/doc/qcad 

.include <bsd.port.mk>
