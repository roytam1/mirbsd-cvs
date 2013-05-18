# $MirOS: ports/games/gtkballs/Makefile,v 1.2 2005/03/30 18:13:28 bsiegert Exp $
# $OpenBSD: Makefile,v 1.12 2002/12/29 15:10:07 fgsch Exp $

COMMENT=	"gtk+ clone of the lines ball logic game"

DISTNAME=	gtkballs-2.2.0
CATEGORIES=	games x11
MASTER_SITES=	${HOMEPAGE}dist/ \
		${MASTER_SITE_SUNSITE:=games/strategy/}

HOMEPAGE=	http://gtkballs.antex.ru/


PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

LIB_DEPENDS=	gtk.1.2,gdk.1.2::x11/gtk+1

NO_REGRESS=	Yes
USE_GMAKE=	Yes
USE_X11=	Yes
CONFIGURE_STYLE=gnu dest
CONFIGURE_ARGS=	--localstatedir=/var/games

.include <bsd.port.mk>
