# $MirOS: ports/misc/logjam/Makefile,v 1.3 2005/05/01 13:50:52 bsiegert Exp $
# $OpenBSD: Makefile,v 1.2 2003/02/12 18:14:28 brad Exp $

COMMENT=	"gtk livejournal client"

VERSION=	4.0.1
DISTNAME=	logjam-${VERSION}
CATEGORIES=	misc x11

HOMEPAGE=	http://logjam.danga.com/


# GPL
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	http://logjam.danga.com/download/

MODULES=	devel/gettext devel/pkgconfig

LIB_DEPENDS=	glib-2.0.0.0,gobject-2.0.0.0,gthread-2.0.0.0::devel/glib \
		gtk-x11-2.0.0.0,gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0::x11/gtk+ \
		curl.2::net/curl \
		xml2::textproc/libxml

PORTHOME=	${WRKDIR}

CONFIGURE_ARGS+=	--without-gnome
CONFIGURE_ARGS+=	--with-xmms=runtime

USE_X11=        	Yes
USE_CXX=		Yes
CONFIGURE_STYLE=	gnu

.include <bsd.port.mk>
