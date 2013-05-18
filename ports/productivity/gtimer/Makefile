# $MirOS: ports/productivity/gtimer/Makefile,v 1.3 2006/02/09 09:36:15 tg Exp $
# $OpenBSD: Makefile,v 1.3 2003/07/16 17:37:47 naddy Exp $

COMMENT=			GTK-based time tracker

DISTNAME=		gtimer-1.1.5
CATEGORIES=     	productivity x11

HOMEPAGE=		http://www.radix.net/~cknudsen/gtimer/


# License: GPL
PERMIT_PACKAGE_CDROM=	Yes 
PERMIT_PACKAGE_FTP=	Yes 
PERMIT_DISTFILES_CDROM= Yes 
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}

LIB_DEPENDS=		gtk.1.2,gdk.1.2::x11/gtk+1

USE_X11=		Yes
USE_GMAKE=		Yes

CONFIGURE_STYLE=	gnu

post-install:
	${INSTALL_MAN} ${WRKSRC}/gtimer.1 ${PREFIX}/man/man1
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/gtimer
	${INSTALL_DATA} ${WRKSRC}/FAQ.html ${PREFIX}/share/doc/gtimer
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/gtimer

.include <bsd.port.mk>
