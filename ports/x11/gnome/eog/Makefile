# $MirOS: ports/x11/gnome/eog/Makefile,v 1.2 2006/02/09 11:15:42 tg Exp $
# $OpenBSD: Makefile,v 1.6 2005/02/13 18:50:25 alek Exp $

COMMENT=			Eye of GNOME: an image viewing and cataloging program
DISTNAME=		eog-2.8.2
CATEGORIES=		graphics x11/gnome

HOMEPAGE=		http://www.gnome.org/	

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/eog/2.8/}	
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS=		:p5-XML-Parser-*:textproc/p5-XML-Parser \
			:scrollkeeper-*:textproc/scrollkeeper
LIB_DEPENDS=		gnomeui-2::x11/gnome/libgnomeui
RUN_DEPENDS=		:scrollkeeper-*:textproc/scrollkeeper
			

USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

CONFIGURE_ARGS+=	--with-gconf-schema-file-dir=${LOCALBASE}/share/schemas/eog \
			--disable-schemas-install

FLAVORS=		exif
FLAVOR?=

.if ${FLAVOR:L:Mexif}
CONFIGURE_ARGS+=	--with-libexif
LIB_DEPENDS+=		exif::graphics/libexif
.else
CONFIGURE_ARGS+=	--without-libexif
.endif

post-patch:
	@ln -s /usr/bin/true ${WRKDIR}/bin/scrollkeeper-update

.include <bsd.port.mk>
