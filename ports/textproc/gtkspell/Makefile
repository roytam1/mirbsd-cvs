# $MirOS$
# $OpenBSD: Makefile,v 1.8 2004/04/13 01:34:57 jolan Exp $

COMMENT=	"gtk2 spelling checker"
DISTNAME=	gtkspell-2.0.5
CATEGORIES=	textproc x11
MASTER_SITES=	${HOMEPAGE}download/
HOMEPAGE=	http://gtkspell.sourceforge.net/

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

USE_X11=	Yes
USE_CXX=	yes

BUILD_DEPENDS=	:pkgconfig-*:devel/pkgconfig
LIB_DEPENDS=	aspell.15.2::textproc/aspell/core \
		gdk_pixbuf-2.0.0.0,gdk-x11-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+

CONFIGURE_STYLE=gnu
CONFIGURE_ENV+=	CPPFLAGS="-I${LOCALBASE}/include" \
		LDFLAGS="-L${LOCALBASE}/lib"
CONFIGURE_ARGS+=--disable-gtk-doc

.include <bsd.port.mk>
