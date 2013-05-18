# $MirOS: ports/graphics/gdk-pixbuf/Makefile,v 1.8 2007/04/03 19:42:54 tg Exp $
# $OpenBSD: Makefile,v 1.30 2004/03/02 07:57:21 brad Exp $

COMMENT=		GdkPixbuf graphics library
VERSION=		0.22.0
DISTNAME=		gdk-pixbuf-${VERSION}
CATEGORIES=		graphics
HOMEPAGE=		http://developer.gnome.org/arch/imaging/gdkpixbuf.html

# GNU GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gdk-pixbuf/0.22/}

USE_X11=		Yes
CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--disable-modules \
			--disable-mmx \
			--disable-gtk-doc \
			--with-html-dir=${PREFIX:Q}/share/doc

LIB_DEPENDS+=		jpeg.62::graphics/jpeg \
			tiff.35.::graphics/tiff \
			gtk.1.2,gdk.1.2::x11/gtk+1
MODULES+=		graphics/png

.include <bsd.port.mk>
