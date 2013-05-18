# $MirOS: ports/x11/gtk+extra/Makefile,v 1.2 2005/03/30 18:13:56 bsiegert Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2003/01/22 17:10:59 margarida Exp $

COMMENT=			GTK Extra Widget Set

DISTNAME=	gtk+extra-0.99.17
CATEGORIES=	x11 devel

HOMEPAGE=	http://gtkextra.sourceforge.net

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${HOMEPAGE}/src/

LIB_DEPENDS=	gtk.1.2,glib.1.2::x11/gtk+1

USE_GMAKE=		Yes
CONFIGURE_STYLE=	gnu

.include <bsd.port.mk>
