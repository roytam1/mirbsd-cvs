# $MirOS: ports/x11/gtk-engines0/Makefile,v 1.1.7.1 2005/03/18 16:00:44 tg Exp $
# $OpenBSD: Makefile,v 1.10 2003/12/09 22:06:23 marcm Exp $

COMMENT=			sample theme engines for GTK+ provided with GNOME
DISTNAME=		gtk-engines-0.12
CATEGORIES=		x11
HOMEPAGE=		http://www.gnome.org
MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gtk-engines/0.12/}
LIB_DEPENDS=		gdk_imlib.19::graphics/imlib

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
CONFIGURE_STYLE= 	autoconf
CONFIGURE_ARGS+= 	${CONFIGURE_SHARED}

.include <bsd.port.mk>
