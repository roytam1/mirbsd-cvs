# $MirOS$
# $OpenBSD: Makefile,v 1.6 2004/03/13 15:40:01 sturm Exp $

COMMENT=		desktop wallpaper manager and X11 screensaver
DISTNAME=		chbg-1.5
DASH_VER=		1
CATEGORIES=     	x11
HOMEPAGE=		http://chbg.sf.net
EXTRACT_SUFX=		.tgz

# License: GPL
PERMIT_PACKAGE_CDROM=	Yes 
PERMIT_PACKAGE_FTP=	Yes 
PERMIT_DISTFILES_CDROM= Yes 
PERMIT_DISTFILES_FTP=	Yes 

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=chbg/}

LIB_DEPENDS=		gdk_imlib.19::graphics/imlib
MODULES+=		graphics/png

CONFIGURE_ARGS=		--with-image-library=gdkimlib \
			--with-imlib1-config=${LOCALBASE}/bin/imlib-config \
			--with-gtk-config=${LOCALBASE}/bin/gtk-config

# Will install some stub files for gnome. Needed if Gnome not installed
# when packaging.
FAKE_FLAGS=		${DESTDIRNAME}=${WRKINST} \
			GNOME_PREFIX=${PREFIX}

USE_X11=		Yes
USE_CXX=		Yes # depends on libungif, which uses CXX
CONFIGURE_STYLE=	gnu

.if ${MACHINE_ARCH} == "sparc64"
PATCH_LIST=		patch-* gcc-*
.endif

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/chbg
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/chbg
	${INSTALL_DATA} ${WRKSRC}/xscreensaver-howto.txt ${PREFIX}/share/doc/chbg
	${INSTALL_DATA} ${WRKSRC}/chbgrc.sample ${PREFIX}/share/examples/chbg

.include <bsd.port.mk>
