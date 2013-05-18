# $MirOS: ports/games/corewars/Makefile,v 1.2 2005/03/30 18:13:26 bsiegert Exp $
# $OpenBSD: Makefile,v 1.4 2002/12/29 15:10:07 fgsch Exp $
COMMENT=			computer simulation game

VERSION=	0.9.12
DISTNAME=	corewars-${VERSION}

CATEGORIES=	games x11

HOMEPAGE=	http://corewars.sourceforge.net/


# GPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

LIB_DEPENDS=	gtk.1.2,gdk::x11/gtk+1

USE_X11=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=corewars/}

CONFIGURE_STYLE=gnu

.include <bsd.port.mk>
