# $MirOS: ports/infrastructure/mk/qt4.port.mk,v 1.1 2008/08/10 09:16:48 bsiegert Exp $

USE_CXX=		Yes

ONLY_FOR_PLATFORM=	Darwin:*:*

QTDIR=			${LOCALBASE}/qt4
MODQT_MOC=		${QTDIR}/bin/moc
MODQT_UIC=		${QTDIR}/bin/uic

.if ${MODQT_NO_DEPENDS:L} != "yes"
LIB_DEPEDS+=		../qt4/lib/QtCore.la::aqua/qt4
.endif
