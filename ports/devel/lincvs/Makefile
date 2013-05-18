# $OpenBSD: Makefile,v 1.13 2004/02/25 02:35:15 naddy Exp $

COMMENT=	"graphical CVS front-end using QT2"
DISTNAME=	lincvs-0.4.90
CATEGORIES=	devel
HOMEPAGE=	http://www.lincvs.org

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	http://lincvs.sunsite.dk/download/${DISTNAME}/
EXTRACT_SUFX=	-0-generic-src.tgz

USE_GMAKE=	Yes
USE_X11=	Yes

MODULES=	x11/qt2

BUILD_DEPENDS=	::x11/qt2-designer

CONFIGURE_STYLE=gnu
CONFIGURE_ARGS=	${MODQT_CONFIGURE_ARGS} \
		--datadir=${LOCALBASE}/share/doc
LDFLAGS+=	-L${MODQT_LIBDIR}
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/auxdir

.include <bsd.port.mk>
