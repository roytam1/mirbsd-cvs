# $MirOS: ports/net/gmudix/Makefile,v 1.4 2006/02/09 11:12:15 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/07/22 22:02:32 jolan Exp $

COMMENT=			Gnome2 MUD/Moo Client

DISTNAME=		gmudix-0.10
CATEGORIES=		net x11
HOMEPAGE=		http://dw.nl.eu.org/mudix.html
MASTER_SITES=		http://dw.nl.eu.org/gmudix/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
USE_CXX=		Yes

MODULES+=		devel/pkgconfig
LIB_DEPENDS=		glib-2.0.0.0,gthread-2.0.0.0::devel/glib \
			gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+

CONFIGURE_STYLE=	gnu

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/gmudix
	${INSTALL_DATA} ${WRKSRC}/doc/gmudix.txt ${PREFIX}/share/doc/gmudix

.include <bsd.port.mk>
