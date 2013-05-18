# $MirOS: ports/net/xchat2/Makefile,v 1.3 2005/07/07 21:25:14 bsiegert Exp $
# $OpenBSD: Makefile,v 1.9 2004/04/10 18:48:30 couderc Exp $

COMMENT=	"GTK+2 IRC client"
MAJOR=		2.0
VERSION=	${MAJOR}.8
DISTNAME=	xchat-${VERSION}
PKGNAME=	xchat2-${VERSION}-0
CATEGORIES=	net x11
HOMEPAGE=	http://www.xchat.org/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${HOMEPAGE}files/source/2.0/
MASTER_SITES0=	${MASTER_SITE_SOURCEFORGE:=xchat/}

EXTRACT_SUFX=	.tar.bz2

LIB_DEPENDS=	gtk-x11-2.0.0.0,gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0::x11/gtk+
MODULES=	devel/gettext devel/pkgconfig
USE_X11=	Yes
CONFIGURE_STYLE=autoconf
AUTOCONF_NEW=	Yes
CONFIGURE_ARGS+=--disable-python --enable-textfe \
		--disable-perl --disable-mmx \
		--enable-ipv6 --enable-openssl="/usr"

.include <bsd.port.mk>
