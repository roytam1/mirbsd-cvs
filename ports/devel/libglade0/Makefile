# $MirOS$
# $OpenBSD: Makefile,v 1.13 2002/12/03 22:45:33 pvalchev Exp $

COMMENT=		library for loading GLADE interface files at runtime

DISTNAME=		libglade-0.17
DASH_VER=		1
CATEGORIES=		devel

HOMEPAGE=		http://www.gnome.org

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/libglade/0.17/}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		devel/gettext
LIB_DEPENDS=		xml.9::textproc/libxml1 \
			gtk.1.2,gdk.1.2::x11/gtk+1

USE_X11=		Yes
CONFIGURE_STYLE= 	gnu
CONFIGURE_ARGS+= 	${CONFIGURE_SHARED}
CONFIGURE_ARGS+= 	--disable-gnomedb
CONFIGURE_ARGS+=	--without-gnome

.include <bsd.port.mk>
