# $MirOS: ports/x11/rep-gtk/Makefile,v 1.3 2005/03/30 18:14:00 bsiegert Exp $
# $OpenBSD: Makefile,v 1.9 2003/05/15 08:52:57 margarida Exp $

COMMENT=			GTK+ binding for librep Lisp environment

VERSION=	0.15
DISTNAME=	rep-gtk-${VERSION}
CATEGORIES=     x11

HOMEPAGE=       http://rep-gtk.sourceforge.net/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=   ${MASTER_SITE_SOURCEFORGE:=rep-gtk/}

LIB_DEPENDS= 	gtk.1.2,gdk.1.2::x11/gtk+1 \
		glib.1.2::devel/glib1 \
		rep.10::lang/librep

SUBST_VARS=     OPSYS_VER VERSION

USE_X11=	Yes
USE_GMAKE=      Yes
CONFIGURE_STYLE= gnu
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --without-gdk-pixbuf --without-gnome --without-libglade

NO_REGRESS=	Yes

.include <bsd.port.mk>
