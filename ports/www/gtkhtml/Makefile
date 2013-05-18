# $MirOS: ports/www/gtkhtml/Makefile,v 1.2 2005/03/25 23:13:37 bsiegert Exp $
# $OpenBSD: Makefile,v 1.6 2003/04/10 15:55:48 marcm Exp $

BROKEN=			needs update to GNOME 2

COMMENT=		"lightweight HTML rendering/printing/editing engine"

DISTNAME=		gtkhtml-1.1.10
CATEGORIES=    		www
HOMEPAGE=		http://www.gnome.org/


# GPL/LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gtkhtml/1.1/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext

LIB_DEPENDS=		bonobo.2,bonobox.2::x11/gnome/bonobo \
			capplet::x11/gnome/controlcenter \
			gal.22::devel/gal \
			ghttp.1::www/libghttp \
			glade.5,glade-gnome.5::devel/libglade,gnome

USE_X11=		Yes
USE_GMAKE=		Yes

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=        ${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--with-bonobo
CONFIGURE_ARGS+= 	--with-gconf
CONFIGURE_ARGS+= 	--disable-gtk-doc

.include <bsd.port.mk>
