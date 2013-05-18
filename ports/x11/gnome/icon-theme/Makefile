# $MirOS: ports/x11/gnome/icon-theme/Makefile,v 1.2 2005/12/29 18:14:26 bsiegert Exp $
# $OpenBSD: Makefile,v 1.7 2004/12/10 20:36:43 marcm Exp $

COMMENT=			the base GNOME icon theme

DISTNAME=		gnome-icon-theme-2.12.1
CATEGORIES=		x11 x11/gnome

HOMEPAGE=		http://www.gnome.org
MASTER_SITES=		${MASTER_SITE_GNOME:=sources/gnome-icon-theme/2.12/}
EXTRACT_SUFX=           .tar.bz2

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes


BUILD_DEPENDS=		:gettext->=0.10.38:devel/gettext \
			:hicolor-icon-theme-*:x11/hicolor-icon-theme \
			::textproc/p5-XML-Parser
RUN_DEPENDS=		:hicolor-icon-theme-*:x11/hicolor-icon-theme

USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE= 	gnu

.include <bsd.port.mk>
