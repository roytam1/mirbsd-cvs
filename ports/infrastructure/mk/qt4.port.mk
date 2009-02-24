# $MirOS: ports/infrastructure/mk/qt4.port.mk,v 1.3 2009/01/03 20:37:45 bsiegert Exp $

USE_CXX=		Yes

ONLY_FOR_PLATFORM=	Darwin:*:*

QTDIR=			${LOCALBASE}/qt4
MODQT_MOC=		${QTDIR}/bin/moc
MODQT_UIC=		${QTDIR}/bin/uic

.if ${MODQT_NO_DEPENDS:L} != "yes"
LIB_DEPENDS+=		../qt4/lib/QtCore.la::aqua/qt4-mac
.endif
