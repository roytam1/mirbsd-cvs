# $MirOS$
# $OpenBSD: Makefile,v 1.23 2003/03/03 03:01:58 fgsch Exp $

COMMENT=	"desktop organizer software for the palm pilot"
DISTNAME=	jpilot-0.99.2
PKGNAME=	${DISTNAME}
CATEGORIES=	comms palm
MASTER_SITES=	${HOMEPAGE}
HOMEPAGE=	http://www.jpilot.org/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=	pisock.3::comms/pilot-link \
		gtk.1.2,gdk.1.2::x11/gtk+1

MODULES=	devel/gettext
USE_X11=	Yes
USE_CXX=	Yes
CONFIGURE_STYLE=autoconf
AUTOCONF_NEW=	Yes
CONFIGURE_ENV=	CPPFLAGS="-I${LOCALBASE}/include" \
		CFLAGS="-I${LOCALBASE}/include" \
		LDFLAGS="-L${LOCALBASE}/lib"

CONFIGURE_ARGS+=--disable-pl-test

NO_REGRESS=	Yes

.include <bsd.port.mk>
