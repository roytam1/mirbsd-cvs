# $MirOS: ports/x11/gnome/metacity/Makefile,v 1.4 2006/02/09 11:15:46 tg Exp $
# $OpenBSD: Makefile,v 1.12 2004/12/15 13:57:57 alek Exp $

COMMENT=			Boring window manager for the adult in you.

DISTNAME=		metacity-2.8.8
CATEGORIES=		x11 x11/gnome

HOMEPAGE=		http://www.gnome.org/softwaremap/projects/Metacity


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/metacity/2.8/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS=		:p5-XML-Parser-*:textproc/p5-XML-Parser
LIB_DEPENDS=		gconf-2::devel/gconf \
			glade-2.0.0.0::devel/libglade \
			startup-notification-1::devel/startup-notification

USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--with-gconf-schema-file-dir=${LOCALBASE}/share/schemas/metacity
CONFIGURE_ARGS+=	--disable-schemas-install

post-install:
	@${INSTALL_DATA_DIR} ${PREFIX}/share/doc/metacity && \
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/metacity/; \
	${INSTALL_DATA} ${WRKSRC}/doc/theme-format.txt ${PREFIX}/share/doc/metacity/; \
	${INSTALL_DATA} ${WRKSRC}/doc/metacity-theme.dtd ${PREFIX}/share/doc/metacity/

.include <bsd.port.mk>
