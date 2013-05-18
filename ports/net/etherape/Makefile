# $MirOS: ports/net/etherape/Makefile,v 1.2 2005/03/25 23:13:49 bsiegert Exp $
# $OpenBSD: Makefile,v 1.3 2004/02/25 13:59:07 naddy Exp $

IGNORE=		"might be broken, used to use Libtool"

COMMENT=		"graphical network monitor"
DISTNAME=		etherape-0.9.0
CATEGORIES=		net
HOMEPAGE=		http://etherape.sourceforge.net/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=etherape/}

CONFIGURE_STYLE=	gnu
MAKE_ENV+=		LIBTOOL="${LOCALBASE}/bin/libtool"

LIB_DEPENDS=		gtk-x11-2.0.0.11::x11/gtk+ \
			glade-2.0.0.1::devel/libglade \
			gnomeui-2::x11/gnome/libgnomeui
MODULES+=		devel/pkgconfig

USE_CXX=		Yes
USE_X11=		Yes

.include <bsd.port.mk>
