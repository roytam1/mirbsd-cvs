# $MirOS: ports/devel/glade/Makefile,v 1.5 2007/03/31 14:07:35 bsiegert Exp $
# $OpenBSD: Makefile,v 1.15 2003/07/12 06:27:12 marcm Exp $

COMMENT=		free user interface builder for GTK+ and GNOME

DISTNAME=		glade-0.6.4
DASH_VER=		1
CATEGORIES=		devel

HOMEPAGE=		http://glade.gnome.org/

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/glade/0.6/}
EXTRACT_SUFX=		.tar.bz2

LIB_DEPENDS=		gtk.1.2,gdk.1.2::x11/gtk+1
BUILD_DEPENDS=		:scrollkeeper->=0.3.12:textproc/scrollkeeper
RUN_DEPENDS=		:automake->=1.4:devel/automake/1.4 \
			:autoconf->=2.13:devel/autoconf/2.13 \
			::devel/metaauto \
			:scrollkeeper->=0.3.12:textproc/scrollkeeper

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
CONFIGURE_STYLE= 	gnu
CONFIGURE_ARGS+= 	--without-bonobo
CONFIGURE_ARGS+=	--disable-gnome

.include <bsd.port.mk>
