# $MirOS: ports/games/gtkpool/Makefile,v 1.2 2005/03/30 18:13:29 bsiegert Exp $
# $OpenBSD: Makefile,v 1.17 2004/04/18 17:21:13 pvalchev Exp $

COMMENT=			simple gtk+ pool simulation game

DISTNAME=	gtkpool-0.5.0
CATEGORIES=	games x11
MASTER_SITES=	${HOMEPAGE}	

HOMEPAGE=	http://gtkpool.seul.org/

LIB_DEPENDS=	gtk.1.2,gdk.1.2::x11/gtk+1


PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

USE_X11=	Yes
USE_CXX=	Yes
NO_REGRESS=	Yes

CONFIGURE_STYLE= gnu
CONFIGURE_ENV=	LIBS="-lossaudio"

.include <bsd.port.mk>
