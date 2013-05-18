# $MirOS: ports/x11/gnome/gdm/Makefile,v 1.4 2007/04/18 20:05:04 bsiegert Exp $
# $OpenBSD: Makefile,v 1.3 2004/01/30 13:36:51 marcm Exp $

COMMENT=		GNOME display manager

DISTNAME=		gdm-2.4.4.7
CATEGORIES=		x11/gnome

HOMEPAGE=		http://www.jirka.org/gdm.html

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gdm/2.4/}
EXTRACT_SUFX=		.tar.bz2

BUILD_DEPENDS=		:scrollkeeper->=0.3.12:textproc/scrollkeeper \
			:p5-XML-Parser-*:textproc/p5-XML-Parser
RUN_DEPENDS=		:scrollkeeper->=0.3.12:textproc/scrollkeeper
LIB_DEPENDS=		gnomeui-2::x11/gnome/libgnomeui \
			rsvg-2::x11/gnome/librsvg
MODULES+=		devel/pkgconfig


CONFDIR=		${SYSCONFDIR}/X11
USE_CXX=		Yes # fam, shared-mime-info, cups, libgsf
USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf old
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--sysconfdir="${CONFDIR}"
CONFIGURE_ARGS+=	--localstatedir=/var
SUBST_VARS=		CONFDIR

post-patch:
	@printf '#!/bin/sh\nexit 0\n' >${WRKDIR:Q}/bin/scrollkeeper-update
	@chmod +x ${WRKDIR:Q}/bin/scrollkeeper-update

post-install:
	@${INSTALL_DATA_DIR} ${PREFIX}/share/examples/gdm; \
	cp -Rp ${WRKINST}/${CONFDIR}/* ${PREFIX}/share/examples/gdm/

.include <bsd.port.mk>
