# $MirOS: ports/net/gtk-gnutella/Makefile,v 1.5 2008/10/04 19:03:22 tg Exp $
# $OpenBSD: Makefile,v 1.14 2004/05/15 14:35:01 sturm Exp $

COMMENT=			Gtk-based GUI client for the Gnutella Network

DISTNAME=		gtk-gnutella-0.93.3
CATEGORIES=     	net 

HOMEPAGE=		http://gtk-gnutella.sourceforge.net/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=gtk-gnutella/}
EXTRACT_SUFX=		.tar.bz2

MODULES+=		devel/pkgconfig
LIB_DEPENDS=		gtk.1.2,gdk.1.2::x11/gtk+1 \
			xml2::textproc/libxml

USE_X11=		Yes

CONFIGURE_STYLE=	simple
CONFIGURE_SCRIPT=	Configure
# -d don't run interactively
# -e fixes bulk package build
CONFIGURE_ARGS=		-d  -e \
			-D mansrc="${PREFIX}/man/man1" \
			-D prefix="${PREFIX}" \
			-D privlib="${PREFIX}/share/gtk-gnutella" \
			-D cc=${_PASS_CC:T:Q} \
			-D ccflags="${CFLAGS} -I${LOCALBASE}/include" \
			-D official="true" \
			-U optimize

FAKE_FLAGS=		INSTALL_PREFIX=${DESTDIR}
INSTALL_TARGET=		install install.man

.include <bsd.port.mk>
