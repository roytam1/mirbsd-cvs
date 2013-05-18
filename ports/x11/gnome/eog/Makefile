# $MirOS: ports/x11/gnome/eog/Makefile,v 1.5 2008/03/09 17:23:43 tg Exp $
# $OpenBSD: Makefile,v 1.6 2005/02/13 18:50:25 alek Exp $

COMMENT=		Eye of GNOME: an image viewing and cataloging program
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
USE_CXX=		Yes # fam, shared-mime-info
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

CONFIGURE_ARGS+=	--with-gconf-schema-file-dir=${LOCALBASE}/share/schemas/eog \
			--disable-schemas-install

FLAVOURS=		exif
FLAVOUR?=

.if ${FLAVOUR:L:Mexif}
CONFIGURE_ARGS+=	--with-libexif
LIB_DEPENDS+=		exif::graphics/libexif
.else
CONFIGURE_ARGS+=	--without-libexif
.endif

post-patch:
	@printf '#!/bin/sh\nexit 0\n' >${WRKDIR:Q}/bin/scrollkeeper-update
	@chmod +x ${WRKDIR:Q}/bin/scrollkeeper-update

.include <bsd.port.mk>
