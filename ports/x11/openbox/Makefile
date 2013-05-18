# $MirOS: ports/x11/openbox/Makefile,v 1.3 2006/02/09 11:15:53 tg Exp $
# $OpenBSD: Makefile,v 1.18 2004/04/24 22:09:55 robert Exp $

COMMENT=	"small, fast & usable window manager"

DISTNAME=	openbox-3.2
PKGNAME=	${DISTNAME}-1
CATEGORIES=	x11
MASTER_SITES=	http://icculus.org/openbox/releases/

HOMEPAGE=	http://www.openbox.org/


MODULES=	devel/gettext devel/pkgconfig
LIB_DEPENDS+=	gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+ \
		xml2.2.6::textproc/libxml \
		startup-notification-1.0.0::devel/startup-notification

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=	Yes
USE_GMAKE=	Yes
CONFIGURE_STYLE= gnu

NO_REGRESS=	Yes

post-install:
	${INSTALL_DATA} ${WRKSRC}/data/*.xml ${PREFIX}/share/openbox

.include <bsd.port.mk>
