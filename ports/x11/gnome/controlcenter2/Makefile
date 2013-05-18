# $MirOS: ports/x11/gnome/controlcenter2/Makefile,v 1.1.7.1 2005/03/18 16:00:21 tg Exp $
# $OpenBSD: Makefile,v 1.12 2004/12/15 13:57:56 alek Exp $

COMMENT=		"GNOME control center"

VERSION=		2.8.1
DISTNAME=		control-center-${VERSION}
CATEGORIES=		x11 x11/gnome
HOMEPAGE=		http://www.gnome.org/


MASTER_SITES=		${MASTER_SITE_GNOME:=sources/control-center/2.8/}
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

LIB_DEPENDS=		xklavier::x11/libxklavier1 \
			metacity-private::x11/gnome/metacity \
			nautilus::x11/gnome/nautilus
BUILD_DEPENDS=		:p5-XML-Parser-*:textproc/p5-XML-Parser

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE= 	autoconf old
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--sysconfdir="${SYSCONFDIR}/gnome"
CONFIGURE_ARGS+=	--with-gconf-schema-file-dir=${LOCALBASE}/share/schemas/control-center2

post-install:
	@${INSTALL_DATA_DIR} ${PREFIX}/share/examples/controlcenter2; \
	cp -Rp ${WRKINST}/${SYSCONFDIR}/gnome/* ${PREFIX}/share/examples/controlcenter2/

.include <bsd.port.mk>
