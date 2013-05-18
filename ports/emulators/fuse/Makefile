# $MirOS: ports/emulators/fuse/Makefile,v 1.6 2008/03/09 17:22:40 tg Exp $
# $OpenBSD: Makefile,v 1.6 2004/05/08 06:46:45 sturm Exp $
# $RuOBSD: Makefile,v 1.7 2002/03/26 19:14:05 grange Exp $

COMMENT=			Free Unix Spectrum Emulator

DISTNAME=		fuse-0.6.2.1
PKGNAME=		${DISTNAME}-1
CATEGORIES=		emulators

HOMEPAGE=		http://fuse-emulator.sourceforge.net/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=fuse-emulator/}

USE_X11=		Yes

LIB_DEPENDS=		glib-2.0.0.0,gmodule-2.0.0.0,gobject-2.0.0.0::devel/glib \
			spectrum::devel/libspectrum \
			765::devel/lib765 \
			xml2::textproc/libxml
MODULES+=		devel/pkgconfig graphics/png

CONFIGURE_STYLE=	gnu
CONFIGURE_ENV=		LIBS="-lbz2"

FLAVOURS=gtk
FLAVOUR?=

.if ${FLAVOUR:L:Mgtk}
LIB_DEPENDS+=		gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+2
CONFIGURE_ARGS=		--with-gtk2
.else
CONFIGURE_ARGS=		--without-gtk
.endif

.include <bsd.port.mk>
