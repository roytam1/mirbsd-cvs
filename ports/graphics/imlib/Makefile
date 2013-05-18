# $MirOS: ports/graphics/imlib/Makefile,v 1.6 2006/02/09 11:11:49 tg Exp $
# $OpenBSD: Makefile,v 1.46 2003/11/14 23:52:42 brad Exp $
# $FreeBSD: Makefile,v 1.45 1999/03/09 01:08:57 nectar Exp $

COMMENT=		"image manipulation library for X11"
DISTNAME=		imlib-1.9.15
PKGNAME=		${DISTNAME}-2
CATEGORIES=		graphics devel
MASTER_SITES=		${MASTER_SITE_GNOME:=sources/imlib/1.9/}
HOMEPAGE=		http://freshmeat.net/projects/imlib/

LIB_DEPENDS+=		gtk.1.2,gdk.1.2::x11/gtk+1 \
			jpeg.62::graphics/jpeg \
			tiff.35::graphics/tiff
MODULES+=		graphics/png

# GNU GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

VMEM_WARNING=		Yes
USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-modules
CONFIGURE_ARGS+=	--disable-nls

FLAVORS=		no_cxx
FLAVOR?=

.if ${FLAVOR:L:Mno_cxx}
CONFIGURE_ARGS+=	--disable-gif
.else
LIB_DEPENDS+=		ungif::graphics/libungif
USE_CXX=		Yes
.endif

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/aclocal
	${INSTALL_DATA} ${WRKSRC}/imlib.m4 ${PREFIX}/share/aclocal/

.include <bsd.port.mk>
