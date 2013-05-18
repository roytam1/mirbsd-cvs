# $MirOS: ports/x11/gnome/ggv/Makefile,v 1.6 2007/07/15 21:26:06 bsiegert Exp $
# $OpenBSD: Makefile,v 1.6 2005/03/06 10:51:07 alek Exp $

COMMENT=		GNOME frontend for GhostScript
DISTNAME=		ggv-2.12.0
CATEGORIES=		print x11/gnome

HOMEPAGE=		http://www.gnome.org/	

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/ggv/2.12/}	
EXTRACT_SUFX=		.tar.bz2

MODULES=		devel/gettext devel/pkgconfig

BUILD_DEPENDS+=		:p5-XML-Parser-*:textproc/p5-XML-Parser
LIB_DEPENDS+=		gnomeui-2::x11/gnome/libgnomeui
B_R_DEPENDS+=		:scrollkeeper-*:textproc/scrollkeeper \
			:ghostscript-*:print/ghostscript/artifex

USE_X11=		Yes
USE_CXX=		Yes # fam, shared-mime-info
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

CONFIGURE_ARGS+=	--with-gconf-schema-file-dir=${LOCALBASE}/share/schemas/ggv \
			--disable-schemas-install

post-patch:
	@printf '#!/bin/sh\nexit 0\n' >${WRKDIR:Q}/bin/scrollkeeper-update
	@chmod +x ${WRKDIR:Q}/bin/scrollkeeper-update

.include <bsd.port.mk>
