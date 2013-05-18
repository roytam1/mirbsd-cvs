# $MirOS: ports/games/gnocatan/Makefile,v 1.1.7.1 2005/03/18 15:46:15 tg Exp $
# $OpenBSD: Makefile,v 1.2 2003/04/24 09:30:32 sturm Exp $

COMMENT=	"Settlers of Catan for GNOME/Gtk"
VERSION=	0.6.1
DISTNAME=	gnocatan-${VERSION}
CATEGORIES=	games x11/gnome
HOMEPAGE=	http://gnocatan.sourceforge.net/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=gnocatan/}

LIB_DEPENDS=	art_lgpl.4,gnome.36,gnomeui.46,gnomesupport.0::x11/gnome/libs

USE_GMAKE=	Yes
USE_X11=	Yes
USE_CXX=	Yes
CONFIGURE_STYLE=autoconf

.include <bsd.port.mk>
