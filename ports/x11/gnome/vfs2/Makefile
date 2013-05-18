# $MirOS: ports/x11/gnome/vfs2/Makefile,v 1.7 2005/12/29 18:38:33 bsiegert Exp $
# $OpenBSD: Makefile,v 1.14 2004/12/15 13:57:57 alek Exp $

COMMENT=			GNOME Virtual File System

VERSION=		2.12.2
DISTNAME=		gnome-vfs-${VERSION}
PKGNAME=		${DISTNAME}-1
CATEGORIES=		devel x11/gnome
HOMEPAGE=		http://www.gnome.org/


MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gnome-vfs/2.12/}

MODULES=		devel/gettext devel/pkgconfig

LIB_DEPENDS=		bonobo-2,bonobo-activation::x11/gnome/libbonobo \
			bz2::archivers/bzip2 \
			cdda_paranoia,cdda_interface::audio/cdparanoia \
			gconf-2::devel/gconf \
			fam::sysutils/fam

BUILD_DEPENDS=		:p5-XML-Parser-*:textproc/p5-XML-Parser \
			:gnome-mime-data->=2.0.0:x11/gnome/mime-data \
			:intltool-*:textproc/intltool \
			:gnome-common-*:x11/gnome/common
RUN_DEPENDS=		:gnome-mime-data->=2.0.0:x11/gnome/mime-data \
			:shared-mime-info-*:misc/shared-mime-info

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autogen old
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
LDFLAGS+=		-pthread
CONFIGURE_ARGS+= 	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--sysconfdir="${SYSCONFDIR}/gnome"
CONFIGURE_ARGS+=	--disable-gtk-doc
CONFIGURE_ARGS+=	--with-gconf-schema-file-dir=${LOCALBASE}/share/schemas/gnome-vfs2
CONFIGURE_ARGS+=	--disable-ipv6
CONFIGURE_ARGS+=	--enable-cdda

post-install:
	@${INSTALL_DATA_DIR} ${PREFIX}/share/examples/gnome-vfs2; \
	cp -Rp ${WRKINST}/${SYSCONFDIR}/gnome/* ${PREFIX}/share/examples/gnome-vfs2/

.include <bsd.port.mk>
