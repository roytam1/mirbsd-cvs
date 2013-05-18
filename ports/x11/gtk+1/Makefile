# $MirOS: ports/x11/gtk+1/Makefile,v 1.6 2005/12/28 16:38:05 tg Exp $
# $OpenBSD: Makefile,v 1.55 2004/01/20 13:41:41 marcm Exp $

COMMENT=			General Toolkit for X11 GUI
DISTNAME=	gtk+-1.2.10
PKGNAME=	${DISTNAME}-4
CATEGORIES=	x11 devel
MASTER_SITES=   ${MASTER_SITE_GNOME:=sources/gtk+/1.2/}
HOMEPAGE=	http://www.gtk.org/
LIB_DEPENDS=	glib.1.2,gmodule.1.2::devel/glib1

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--with-xinput="xfree" \
			--disable-glibtest \
			--disable-nls

post-extract:
	@cd ${WRKSRC}/docs; rm -f gtk.info* gdk.info*

.include <bsd.port.mk>
