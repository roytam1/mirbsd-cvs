# $MirOS$
# $OpenBSD: Makefile,v 1.55 2004/01/20 13:41:41 marcm Exp $

COMMENT=	"General Toolkit for X11 GUI"
DISTNAME=	gtk+-1.2.10
PKGNAME=	${DISTNAME}p1
CATEGORIES=	x11 devel
MASTER_SITES=   ${MASTER_SITE_GNOME:=sources/gtk+/1.2/}
HOMEPAGE=	http://www.gtk.org/
MODULES=	devel/gettext
LIB_DEPENDS=	glib.1.2,gmodule.1.2::devel/glib

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=	Yes
CONFIGURE_STYLE= autoconf
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --enable-static --with-xinput="xfree"
CONFIGURE_ARGS+= --disable-glibtest
CONFIGURE_ENV=	CPPFLAGS="-I${LOCALBASE}/include" \
		LDFLAGS="-L${LOCALBASE}/lib"

post-extract:
	@cd ${WRKSRC}/docs; rm -f gtk.info* gdk.info*

.include <bsd.port.mk>
