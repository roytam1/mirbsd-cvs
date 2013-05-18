# $MirOS: ports/x11/gnome/libgnome/Makefile,v 1.5 2007/04/18 20:05:05 bsiegert Exp $
# $OpenBSD: Makefile,v 1.10 2004/12/15 13:57:56 alek Exp $

COMMENT=		libraries for the GNOME project

DISTNAME=		libgnome-2.18.0
CATEGORIES=		x11/gnome

HOMEPAGE=		http://www.gnome.org/


# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/libgnome/2.18/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS=		:p5-XML-Parser-*:textproc/p5-XML-Parser
LIB_DEPENDS=		esd.0.2::audio/esound \
			gnomevfs-2::x11/gnome/vfs2 \
			audiofile::devel/libaudiofile \
			xslt.1::textproc/libxslt

USE_X11=		Yes
USE_CXX=		Yes # fam, shared-mime-info
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf old
AUTOCONF_NEW=		yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--sysconfdir="${SYSCONFDIR}/gnome"
CONFIGURE_ARGS+=	--disable-gtk-doc
CONFIGURE_ARGS+=	--with-gconf-schema-file-dir=${LOCALBASE}/share/schemas/libgnome

post-install:
	@${INSTALL_DATA_DIR} ${PREFIX}/share/examples/libgnome; \
	cp -Rp ${WRKINST}/${SYSCONFDIR}/gnome/* ${PREFIX}/share/examples/libgnome/

.include <bsd.port.mk>
